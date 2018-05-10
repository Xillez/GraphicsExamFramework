#include "Renderer.hpp"

auto modeler::Renderer::registerModel(std::string path) -> std::pair<int, int>
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
        // If new VAO is needed, assign new.
        if (lastVBm > 4)
        {
            lastVAm++;
            lastVBm = 0;
        }

        // Read anm save model.
        //readModem(path)
        //saveModem();

        // Registem the new obect in the map.
        map[path] = std::pair<int, std::pair<int, int>> (1, std::pair<int, int>(lastVAO, lastVBO));
    }
    // Model exists in map.
    else
    {
        // Another object uses this model.
        this->map[match->first]->second.first++;
    }

    // 
    return match->second.second;
}

auto modeler::Renderer::draw(Shader shader, std::pair<int, int> vao_vbo, glm::mat4 model) -> void
{
    for(unsigned int i = 0; i < meshes.size(); i++)
    {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                                            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.id(), (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
}

void modeler::Mesh::createVAOVBO()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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

	glBindVertexArray(0);
}

auto modeler::Renderer::readModel(std::string path) -> void
{
    modeler::Model model = new Model(path);
    model.getMeshes();

}