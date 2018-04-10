#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	void setPos(glm::vec3 pos);
	void setDir(glm::vec3 dir);
	void setUp(glm::vec3 up);
	glm::vec3 getPos();
	glm::vec3 getDir();
	glm::vec3 getUp();

	glm::mat4 getViewMatrix();

private:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

};