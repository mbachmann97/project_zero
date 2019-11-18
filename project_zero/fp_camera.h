#pragma once

#include "camera.h"

class FPCamera : public Camera {
public:
	FPCamera(float32 fov, float32 width, float32 height);

	void OnMouseMoved(float32 xRel, float32 yRel);
	void Update() override;
	void MoveFront(float32 amount);
	void MoveSideways(float32 amount);

protected:
	float32 yaw;
	float32 pitch;
	glm::vec3 lookAt;
	const float32 mouseSensitivity = 0.2f;
	glm::vec3 up;
};

