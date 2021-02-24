#pragma once

#include <cmath>

#include <Core/Engine.h>
#include <string>
#include "Transform3D.h"

class Player
{
public:
	Player(std::string name);
	~Player();
	Mesh* getMesh();
	glm::mat4 getModelMatrix(float deltaTimeSeconds, glm::vec3 positiontarget);
	void moveLeft();
	void moveRight();
	void jump(float deltaTimeSeconds);
	void setjump();
	float getCoordx();
	float getCoordy();
	float getCoordz();
	void increaseSpeed();
	void decreaseSpeed();
	bool isJump();
	void setFall();
	float getFuel();
	void decreaseFuel();
	void increaseFuel();
	void setFuel(float myfuel);
protected:
	//glm::vec3 color;
	std::string name;
	Mesh* mesh;
	float translateX;
	float scale = 0.5f;
	float coordx = 0.5f, coordy = 0.35f, coordz = 0;
	float initcoordx = 0.5f, initcoordy = 0.35f, initcoordz = 0;
	float maxcoordy = 2;
	float angleRotate;
	int speedRotate = 5;
	bool jumpUp = false, jumpDown = false;
	glm::mat4 modelMatrix;
	bool isfall = false;
	bool isfallforx = false;
	float fuel = 15;
};
