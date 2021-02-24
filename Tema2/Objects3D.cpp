#include "Objects3D.h"

#include <Core/Engine.h>
#include <Component/SimpleScene.h>
#define PI 3.14159265359
#define NRPOINTS 150

Mesh* Objects3D::MakeCube(std::string name, glm::vec3 leftFrontBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftFrontBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0, -length), color),
		VertexFormat(corner + glm::vec3(length, 0, -length), color),
		VertexFormat(corner + glm::vec3(0, length, -length), color),
		VertexFormat(corner + glm::vec3(length, length, -length), color)
	};

	Mesh* cube = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 1, 2, 3, 1, 5, 7, 3, 1, 7, 5, 4, 7, 4, 6, 7, 0, 4, 2, 4, 2, 6, 2, 3, 7, 2, 6, 7, 0, 1, 4, 1, 5, 4 };

	cube->InitFromData(vertices, indices);

	return cube;
}
Mesh* Objects3D::MakeBackground(std::string name, glm::vec3 leftFrontBottomCorner, float length, glm::vec3 color) {
	glm::vec3 corner = leftFrontBottomCorner;
	Mesh* background;
	
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 2, 3
	};

	background = CreateMesh(name, vertices, indices);
	return background;
}
Mesh* Objects3D::MakeForeground(std::string name, glm::vec3 leftFrontBottomCorner, float length, glm::vec3 color) {
	glm::vec3 corner = leftFrontBottomCorner;
	Mesh* foreground;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 2, 3
	};
	foreground = CreateMesh(name, vertices, indices);
	return foreground;
}
Mesh* Objects3D::CreateMesh(std::string name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute 
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	Mesh* mesh = new Mesh(name);
	mesh ->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;
	return mesh;
}
Mesh* Objects3D::CreateSphere(std::string name, float radius, glm::vec3 color) {
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	float sStep = 2 * PI / NRPOINTS;
	float step = PI / NRPOINTS;
	float angle;

	for (int i = 0; i <= NRPOINTS; i++) {
		angle = PI / 2 - i * step;
		float xy = radius * cosf(angle);
		for (int j = 0; j <=  NRPOINTS; j++) {
			vertices.emplace_back(glm::vec3(xy * cosf(j * sStep), xy * sinf(j * sStep), radius * sinf(angle)), color);
		}
	}
	for (int i = 0; i < NRPOINTS; i++) {
		int p1 = i * ( NRPOINTS + 1);
		int p2 = p1 +  NRPOINTS + 1;
		for (int j = 0; j < NRPOINTS; j++) {
			if (i != 0) {
				indices.push_back(p1);
				indices.push_back(p2);
				indices.push_back(p1 + 1);
			}

			if (i != ( NRPOINTS - 1)) {
				indices.push_back(p1 + 1);
				indices.push_back(p2);
				indices.push_back(p2 + 1);
			}
			p1++;
			p2++;
		}
	}
	return CreateMesh(name, vertices, indices);
}