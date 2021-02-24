#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Component/SimpleScene.h>

namespace Objects3D
{
	Mesh* MakeCube(std::string name, glm::vec3 leftFrontBottomCorner, float length, glm::vec3 color);
	Mesh* MakeBackground(std::string name, glm::vec3 leftFrontBottomCorner, float length, glm::vec3 color);
	Mesh* MakeForeground(std::string name, glm::vec3 leftFrontBottomCorner, float length, glm::vec3 color);
	Mesh* CreateMesh(std::string name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	Mesh* CreateSphere(std::string name, float radius, glm::vec3 color);
}