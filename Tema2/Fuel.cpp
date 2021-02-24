#include <string>
#include <vector>
#include <iostream>

#include <cmath>

#include <Core/Engine.h>
#include "Fuel.h"
#include "Transform3D.h"
#include "Objects3D.h"
#include <Component/SimpleScene.h>

#define WHITE glm::vec3(1, 1, 1)
#define ROSE glm::vec3(1, 0.5f, 0.6f)

Fuel::Fuel(std::string name) {
	this->name = name;
	background = Objects3D::MakeBackground("background", glm::vec3(0, 0, 0), 1, WHITE);
	foreground = Objects3D::MakeForeground("foreground", glm::vec3(0, 0, 0), 1, ROSE);
}

Fuel::~Fuel() {

}
Mesh* Fuel::getBackground() {
	return this->background;
}
Mesh* Fuel::getForeground() {
	return this->foreground;
}

glm::mat4 Fuel::getModelMatrixBackground(float deltaTimeSeconds, glm::vec3 position) {
	//modelMatrix1 = Transform3D::Translate(1.98, 1, 0);
	modelMatrix1 = Transform3D::Translate(position.x + 2, position.y - 1, position.z - 5);
	modelMatrix1 *= Transform3D::Scale(0.54, 1.26, 1);
	return modelMatrix1;
}
glm::mat4 Fuel::getModelMatrixForeground(float deltaTimeSeconds, float myfuel, glm::vec3 position) {
	modelMatrix2 = Transform3D::Translate(position.x + 2.01, position.y - 0.98, position.z - 4.99);
	modelMatrix2 *= Transform3D::Scale(0.5, 1.2, 1);
	modelMatrix2 *= Transform3D::Scale(1, myfuel / 15, 1);
	return modelMatrix2;
}

