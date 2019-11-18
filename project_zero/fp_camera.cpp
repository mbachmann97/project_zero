#include "fp_camera.h"

FPCamera::FPCamera(float32 fov, float32 width, float32 height) : Camera(fov, width, height) {
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	OnMouseMoved(0.0f, 0.0f);
	Update();
}

void FPCamera::OnMouseMoved(float32 xRel, float32 yRel) {
	yaw += xRel * mouseSensitivity;
	pitch += yRel * mouseSensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(-pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	lookAt = glm::normalize(front);
	Update();
}

void FPCamera::Update() {
	view = glm::lookAt(position, position + lookAt, up);
	viewProj = projection * view;
}

void FPCamera::MoveFront(float32 amount) {
	Translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * lookAt) * amount);
	Update();
}

void FPCamera::MoveSideways(float32 amount) {
	Translate(glm::normalize(glm::cross(lookAt, up)) * amount);
	Update();
}