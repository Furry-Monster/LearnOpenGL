#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tex_coords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	//bone indexes which will influence this vertex
	int m_bone_ids[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_weights[MAX_BONE_INFLUENCE];
};

struct texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class mesh
{
public:
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;

	unsigned int vao;

	mesh(const std::vector<vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<texture>& textures);

	// render the mesh
	void draw(const shader& shader) const;
private:
	unsigned int vbo_, ebo_;

	// initializes all the buffer objects/arrays
	void setup_mesh();
};

#endif