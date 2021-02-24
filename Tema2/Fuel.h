#pragma once

#include <cmath>

#include <Core/Engine.h>
#include <string>
#include "Transform3D.h"

class Fuel
{
public:
	Fuel(std::string name);
	~Fuel();
	Mesh* getBackground();
	Mesh* getForeground();
	glm::mat4 getModelMatrixBackground(float deltaTimeSeconds, glm::vec3 position);
	glm::mat4 getModelMatrixForeground(float deltaTimeSeconds, float myfuel, glm::vec3 position);

	
protected:
	//glm::vec3 color;
	std::string name;
	Mesh* background;
	Mesh* foreground;
	glm::mat4 modelMatrix1;
	glm::mat4 modelMatrix2;
};
