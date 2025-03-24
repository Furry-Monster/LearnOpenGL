// ReSharper disable CppClangTidyModernizeUseDesignatedInitializers
// ReSharper disable CppClangTidyBugproneNarrowingConversions
// ReSharper disable CppClangTidyPerformanceNoIntToPtr
#include "mesh.h"

mesh::mesh(const std::vector<vertex>& vertices,
	const std::vector<unsigned int>& indices,
	const std::vector<texture>& textures)
	: vertices(vertices), indices(indices), textures(textures)
{
	setup_mesh();
}

void mesh::draw(const shader& shader) const
{
	// bind appropriate textures
	unsigned int diffuse_nr = 1;
	unsigned int specular_nr = 1;
	unsigned int normal_nr = 1;
	unsigned int height_nr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);// active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		// number it
		if (name == "texture_diffuse")
			number = std::to_string(diffuse_nr++);
		else if (name == "texture_specular")
			number = std::to_string(specular_nr++);
		else if (name == "texture_normal")
			number = std::to_string(normal_nr++);
		else if (name == "texture_height")
			number = std::to_string(height_nr++);

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void mesh::setup_mesh()
{
	struct attribute {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
	};

	attribute attributes[] = {
		{0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), static_cast<void*>(nullptr)},
		{1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, normal))},
		{2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, tex_coords))},
		{3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, tangent))},
		{4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, bitangent))},
		{5, 4, GL_INT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, m_bone_ids))},
		{6, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, m_weights))}
	};

	// create buffers/arrays
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao);

	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// set the vertex attribute pointers
	for (const auto& [index, size, type, normalized, stride, pointer] : attributes) {
		glEnableVertexAttribArray(index);
		if (type == GL_INT)
			glVertexAttribIPointer(index, size, type, stride, pointer);
		else
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	glBindVertexArray(0);
}

