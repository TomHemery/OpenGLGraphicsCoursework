#include "ColourOperations.h"
//converts a hue value (0-360) to an RGB value
glm::vec3 ColourOperations::HueToRGB(float hue) {
	glm::vec3 colour;
	float x = static_cast<float>(1 - abs((fmod((hue / 60), 2) - 1)));

	if (hue < 60) {
		colour = glm::vec3(1, x, 0);
	}
	else if (hue < 120) {
		colour = glm::vec3(x, 1, 0);
	}
	else if (hue < 180) {
		colour = glm::vec3(0, 1, x);
	}
	else if (hue < 240) {
		colour = glm::vec3(0, x, 1);
	}
	else if (hue < 300) {
		colour = glm::vec3(x, 0, 1);
	}
	else if (hue <= 360) {
		colour = glm::vec3(1, 0, x);
	}

	return colour;
}