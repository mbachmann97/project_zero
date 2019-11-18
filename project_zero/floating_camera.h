#pragma once
#include "fp_camera.h"

class FloatingCamera : public FPCamera {
public:
	FloatingCamera(float32 fov, float32 width, float32 height) : FPCamera(fov, width, height) {}

	void MoveUp(float32 amount) {
		Translate(up * amount);
	}
};
