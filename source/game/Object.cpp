#include "Object.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"
#include "../components/GraphicsComponent.hpp"

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;

game::Object::Object(std::string const &path)
{
	components::GraphicsComponent* component = new components::GraphicsComponent(path);
	component->init(this);
	this->componentList.push_back(component);

	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
	});
}

auto game::Object::update(float dt) -> void
{
	
}

auto game::Object::draw() -> void
{
	this->shaderProgram->bind();

	glm::mat4 view = camera->getViewMatrix(); 
	
	glm::mat4 projection = camera->getPerspectiveMatrix();

	glm::vec3 lightPosition = lightSource->getPosition();
	glm::vec3 attenuation = lightSource->getAttenuation(); 
	glm::vec3 lightColor = lightSource->getColor();

	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, std::string>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"lightSourcePositionID","lightSourcePosition"},
		{"camPosID", "CamPos"},
		{"attenuationAID", "attenuationA"},
		{"attenuationBID", "attenuationB"},
		{"attenuationCID", "attenuationC"},
		{"lightColorID", "lightColor"}
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));

	glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 modelm;

	modelm = glm::translate(modelm, this->position); // Translate it down so it's at the center of the scene.
	modelm = glm::scale(modelm, glm::vec3(0.9f, 0.9f, 0.9f));	

	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	this->componentList.at(0)->draw(*shaderProgram);

	shaderProgram->unbind();
}