#include <string>
#include <vector>
#include <iostream>

#include <cmath>

#include <Core/Engine.h>
#include "Platform.h"
#include "Transform3D.h"
#include "Objects3D.h"
#include <Component/SimpleScene.h>

Platform::Platform(std::string name , glm::vec3 mycolor) {
	this->color = mycolor;
	this->name = name;
	mesh = Objects3D::MakeCube("platform", glm::vec3(0, 0, 0), 1, color);
	
}

Platform::~Platform() {

}
Mesh* Platform::getMesh() {
	return mesh;
}
void Platform::setCoord(float mycoordx, float mycoordy, float mycoordz, float myscalez, float mydistancebehind) {
	coordx = mycoordx;
	coordy = mycoordy;
	coordz = mycoordz;
	scalez = myscalez;
	distancebehind = mydistancebehind;
}
float Platform::getCoordx() {
	return coordx;
}
float Platform::getCoordz() {
	return coordz;
}
float Platform::getScalez() {
	return scalez;
}
float Platform::getDistanceBehind() {
	return distancebehind;
}
void Platform::increaseSpeed() {
	speed += 2;
}
void Platform::decreaseSpeed() {
	speed -= 2;
}
glm::vec3 Platform::getColor() {
	return this->color;
}
void Platform::changeColor() {
	color = glm::vec3(0.4f, 0, 0.5f);
	mesh = Objects3D::MakeCube("platform", glm::vec3(0, 0, 0), 1, color);
}
void Platform::setColor(glm::vec3 mycolor) {
	this->color = mycolor;
	mesh = Objects3D::MakeCube("platform", glm::vec3(0, 0, 0), 1, color);
}
glm::mat4 Platform::getModelMatrix(float deltaTimeSeconds) {
	modelMatrix = glm::mat4(1);
	coordz += speed * deltaTimeSeconds;
	modelMatrix *= Transform3D::Translate(coordx, coordy, coordz);
	modelMatrix *= Transform3D::Scale(1, 0.1f, scalez);
	return modelMatrix;
}
void Platform::stopSpeed() {
	speed = 0;
}
void Platform::blockedSpeed() {
	speed += 6;
}
void Platform::speedNormal() {
	speed -= 6;
}