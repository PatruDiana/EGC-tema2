#pragma once

#include <cmath>

#include <Core/Engine.h>
#include <string>
#include "Transform3D.h"

class Platform
{
public:
	Platform(std::string name, glm::vec3 color);
	~Platform();
	Mesh* getMesh();
	glm::mat4 getModelMatrix(float deltaTimeSeconds);
	void setCoord(float mycoordx, float mycoordy, float mycoordz, float myscalez, float mydistancebehind);
	float getCoordx();
	float getCoordz();
	float getScalez();
	float getDistanceBehind();
	void increaseSpeed();
	void decreaseSpeed();
	void changeColor();
	void setColor(glm::vec3 mycolor);
	void stopSpeed();
	glm::vec3 getColor();
	void blockedSpeed();
	void speedNormal();

protected:
	glm::vec3 color;
	std::string name;
	Mesh* mesh;
	glm::mat4 modelMatrix;
	float coordx = 0, coordy = 0, coordz = 0;
	float distancebehind = 0;
	float scalez = 0;
	float speed = 6;
};
