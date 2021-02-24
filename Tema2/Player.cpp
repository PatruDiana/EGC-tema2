#include <string>
#include <vector>
#include <iostream>

#include <cmath>

#include <Core/Engine.h>
#include "Player.h"
#include "Transform3D.h"
#include "Objects3D.h"
#include <Component/SimpleScene.h>

Player::Player(std::string name) {
	this->name = name;
	//mesh = Objects3D::CreateSphere(name, 0.1f, glm::vec3(1, 1, 1));
	mesh = new Mesh(name);
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
}

Player::~Player() {

}
void Player::setjump() {
	jumpUp = true;
}
Mesh* Player::getMesh() {
	return mesh;
}
float Player::getCoordx() {
	return coordx;
}
float Player::getCoordy() {
	return coordy;
}
float Player::getCoordz() {
	return coordz;
}
bool Player::isJump() {
	return jumpUp || jumpDown;
}
void Player::setFall() {
	isfall = true;
}
float Player::getFuel() {
	return this->fuel;
}
void Player::increaseFuel() {
	fuel += 4;
}
void Player::decreaseFuel() {
	fuel -= 3;
}
void Player::setFuel(float myfuel) {
	fuel = myfuel;
}
glm::mat4 Player::getModelMatrix(float deltaTimeSeconds, glm::vec3 positiontarget) {
	modelMatrix = glm::mat4(1);
	if (isfall) {
		angleRotate = 0;
		if (!isfallforx) {
			isfallforx = true;
			coordz -= 0.5f;
		}
		if (coordy > -3) {
			coordy -= 1.5 * deltaTimeSeconds;
		}
		else {
			exit(0);
		}
	}
	else {
		angleRotate += speedRotate * deltaTimeSeconds;

		if (jumpUp || jumpDown) {
			jump(deltaTimeSeconds);
		}
	}
	
	modelMatrix = Transform3D::Translate(positiontarget.x, positiontarget.y, positiontarget.z);
	modelMatrix *= Transform3D::Scale(scale, scale, scale);
	modelMatrix *= Transform3D::RotateOZ(-angleRotate);
	return modelMatrix;
}
void Player::moveLeft() {
	coordx -=  1;
}

void Player::moveRight() {
	coordx += 1;
}
void Player::increaseSpeed() {
	speedRotate += 2;
}
void Player::decreaseSpeed() {
	speedRotate -= 2;
}
void Player::jump(float deltaTimeSeconds) {
	if (jumpUp) {
		if (coordy < maxcoordy) {
			coordy += 2 * deltaTimeSeconds;
		}
		else {
			jumpUp = false;
			jumpDown = true;
		}
	}
	else if (jumpDown) {
		if (coordy > initcoordy) {
			coordy -= 3 * deltaTimeSeconds;
		}
		else {
			jumpDown = false;
		}
	}
}