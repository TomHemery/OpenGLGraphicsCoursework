#pragma once
#include <glm/glm.hpp>
//class that was designed to perform various colour operations, but actually just converts HSB to RGB
class ColourOperations
{
public:
	static glm::vec3 HueToRGB(float hue);
};

