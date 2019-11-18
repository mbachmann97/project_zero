#pragma once

#include "../dependencies/glm/glm.hpp"
#include "../dependencies/glm/ext/matrix_transform.hpp"
#include "../dependencies/glm/gtc/matrix_transform.hpp"

#include "defines.h"

class Camera {
public:
	Camera(float32 fov, float32 width, float32 height);

	glm::mat4 GetViewProj();
	glm::mat4 GetView();
	virtual void Update();
	virtual void Translate(glm::vec3 direction);

protected:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProj;
};
