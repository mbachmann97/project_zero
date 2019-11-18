#include "camera.h"

Camera::Camera(float32 fov, float32 width, float32 height) {
	projection = glm::perspective(fov / 2.0f, width / height, 0.1f, 1000.0f);
	view = glm::mat4(1.0f);
	position = glm::vec3(0.0f);
	Update();
}

glm::mat4 Camera::GetViewProj() {
	return viewProj;
}

glm::mat4 Camera::GetView() {
	return view;
}

void Camera::Update() {
	viewProj = projection * view;
}

void Camera::Translate(glm::vec3 direction) {
	position += direction;
	view = glm::translate(view, direction * -1.0f);
}