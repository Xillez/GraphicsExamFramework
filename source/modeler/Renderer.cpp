#include "Renderer.hpp"
#include "ShaderManager.hpp"
#include "Model.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include <algorithm>

// Needs namespace infront because compiler wont recognize that it exists.
extern modeler::ShaderManager* shaderManager;
extern environment::Camera* camera;
extern environment::LightSource* lightSource;

modeler::Renderer::Renderer()
{
   // glGenVertexArrays(1, &drawVAO);

    shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
        {GL_VERTEX_SHADER, "../shader/vertex.vert"},
        {GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
    });

    this->shaderProgram->bind();
}
modeler::Renderer::~Renderer(){
    shaderProgram->unbind();
}


auto modeler::Renderer::registerModel(std::string path) -> void
{
    std::unordered_map<
        std::string,            // Key: Path to model
        std::pair<
            int,                // Value 1: Nr of instances registered to the current model in key
            std::pair<
                int,            // Value 2: Which VAO object exists in.
                int             // Value 3: Which VBO object exists in.
            >
        >
    >::const_iterator match = map.find(path);

    // If not found, add to map.
    if (match == map.end())
    {
        // Saving paths for looping later.
        modelPath.push_back(path);

        // If new VAO is needed, assign new.
        if ((lastVBO + 2) > 16)
        {
            lastVAO++;
            lastVBO = 0;
        }

        // Read and save model.
        loadModel(path);


        // Register the new obect in the map.
        map[path] = std::pair<int, std::pair<int, int>> (1, std::pair<int, int>(lastVAO, lastVBO));

        // Start of next object in VBO. Object consists of 4 buffers (vertices, indices, textureCoords, model).
        lastVBO += 2;
    }
    // Model exists in map.
    else
    {
        // Another object uses this model.
        this->map[match->first].first++;
    }

   // return match->second.second;

    // TODO:
    // Sort the map based upon object occurences and set up buffers after all objects register.
    // Do draw instancing.
}

auto modeler::Renderer::draw(std::string path, game::Object* object) -> void
{
    // We can't find the model path, don't draw.
    if (getIndexFromVector(path) == -1)
        return;

    glm::mat4 model = object->getModelMatrix();

    glm::mat4 view = camera->getViewMatrix(); 
    
    glm::mat4 projection = camera->getPerspectiveMatrix();

    glm::vec3 lightPosition = lightSource->getPosition();
    glm::vec3 attenuation = lightSource->getAttenuation(); 
    glm::vec3 lightColor = lightSource->getColor();
    float ambientCoefficient = lightSource->getAmbientCoefficient();
    int specularExponent = lightSource->getSpecularExponent();

    std::map<std::string, GLuint> uniforms = shaderProgram->getUniform( std::map<std::string, std::string>({
        {"viewID", "view"},
        {"projectionID", "projection"},
        {"modelID", "model"},
        {"normalMatrixID", "normalMatrix"},
        {"lightSourcePositionID","lightSourcePosition"},
        {"camPosID", "CamPos"},
        {"attenuationAID", "attenuationA"},
        {"attenuationBID", "attenuationB"},
        {"attenuationCID", "attenuationC"},
        {"ambientCoefficientID", "ambientCoefficient"},
        {"specularExponentID", "specularExponent"},
        {"lightColorID", "lightColor"}
    }));

    glUniform1f(uniforms["attenuationAID"], attenuation.x);
    glUniform1f(uniforms["attenuationBID"], attenuation.y);
    glUniform1f(uniforms["attenuationCID"], attenuation.z);
    glUniform1f(uniforms["ambientCoefficientID"], ambientCoefficient);
    glUniform1i(uniforms["specularExponentID"], specularExponent);
    glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
    glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));

    glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));                                             //glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

    glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(model));

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*model)));

    glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
    
    // TODO: May redraw the same over and over, meshes is a list of all submeshes og objs file. and we draw the entire obj file. 
    //for(unsigned int i = 0; i < modelPath.size(); i++)
    //{
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int j = 0; j < textures[getIndexFromVector(path)].size(); j++)
        {
            glActiveTexture(GL_TEXTURE0 + j); // active proper texture unit before binding
                                            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[getIndexFromVector(path)][j].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shaderProgram->id(), (name + number).c_str()), j);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[getIndexFromVector(path)][j].id);
        }

        // draw mesh
        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, BO[map[path].second.second]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BO[map[path].second.second + 1]);
        glDrawElements(GL_TRIANGLES, indices[getIndexFromVector(path)].size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    //}
}

void modeler::Renderer::createVAOVBO()
{   
    GLuint tempVAO = 0; //!< Vertex array object associated with the mesh. NOTE: VAO  should be associate with multiple meshes.
    GLuint tempVBO = 0; //!< Vertex buffer object for drawing 
    GLuint tempIBO = 0; //!< Vertex element buffer for drawing

    BO.reserve(2 * modelPath.size());
    for(auto v : modelPath){
        printf("Map first: %d\n", map[v].second.first);
        printf("Map second: %d\n", map[v].second.second);
        printf("Size: %d\n", modelPath.size());

        // If the VAO doesnt exists.
        if (std::find(VAO.begin(), VAO.end(), tempVAO) == VAO.end())
        {
            // create buffers/arrays
            glGenVertexArrays(1, &tempVAO);

            // Save the reference to the VAO in a list.
            VAO.push_back(tempVAO);  
        }

        // Bind the VAO.
        glBindVertexArray(VAO[map[v].second.first]);

        // Generate buffers.
        /*glGenBuffers(1, &tempVBO);
        BO.push_back(tempVBO);
        tempVBO = 0;
        glGenBuffers(1, &tempIBO);
        BO.push_back(tempIBO);
        tempIBO = 0;*/

        glGenBuffers(1, &BO[map[v].second.second]);
        glGenBuffers(1, &BO[map[v].second.second + 1]);

        for (int i = 0; i < BO.size(); i++)
        {
            printf("BO size: %d\n", BO[i]);
            
        }

        printf("Nr models: %d\n", getIndexFromVector(v));

        printf("\n\n Vertex data!\n");
        for (int i = 0; i < 100; i++)
            printf("(%f, %f, %f)\n", vertices[getIndexFromVector(v)][i].Position.x, vertices[getIndexFromVector(v)][i].Position.y, vertices[getIndexFromVector(v)][i].Position.z);
        printf("\n End of Vertex data!\n\n");

        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, BO[map[v].second.second]);
        glBufferData(GL_ARRAY_BUFFER, vertices[getIndexFromVector(v)].size() * sizeof(Vertex), &vertices[getIndexFromVector(v)][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BO[map[v].second.second + 1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[getIndexFromVector(v)].size() * sizeof(unsigned int), &indices[getIndexFromVector(v)][0], GL_STATIC_DRAW);
       
        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

auto modeler::Renderer::loadModel(std::string path) -> void
{
    Model model = Model(path);
    this->meshes = model.getMeshes();

    std::vector<Vertex> tempVert;
    std::vector<unsigned int> tempIndi;
    std::vector<TextureA> tempTex;

    for(auto mesh : meshes)
    {
        for (auto vertex : mesh.vertices)
        {
            tempVert.push_back(vertex);
        }
        for (auto index : mesh.indices)
        {
            tempIndi.push_back(index);
        }
        for (auto texture : mesh.textures)
        {
            tempTex.push_back(texture);
        }
    }
    vertices.push_back(tempVert);
    indices.push_back(tempIndi);
    textures.push_back(tempTex);
    printf("Nr vertecies: %d\n", vertices.size());

}

auto modeler::Renderer::getIndexFromVector(std::string item) -> int{
    int pos = std::find(modelPath.begin(), modelPath.end(), item) - modelPath.begin();

    return ((pos >= modelPath.size()) ? -1 : pos);
}
