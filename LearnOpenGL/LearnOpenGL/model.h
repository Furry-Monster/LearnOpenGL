#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "mesh.h"
#include "shader.h"

class model
{
public:
	/*  public functions   */
	model(const char* path, const bool gamma = false);
	void draw(const shader& shader) const;

private:
	/*  data  */
	std::vector<mesh> meshes_;
	std::vector<texture> textures_loaded_;
	std::string directory_;
	bool gamma_correction_;
	/*  private functions  */
	void load_model(const std::string& path);
	void process_node(const aiNode* node, const aiScene* scene);
	mesh process_mesh(aiMesh* mesh_in, const aiScene* scene);
	std::vector<texture> load_material_textures(const aiMaterial* material, aiTextureType type, const std::string& type_name);
};

inline unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma)
{
	auto filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int texture_id;
	glGenTextures(1, &texture_id);

	int width, height, nr_components;
	if (unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nr_components, 0))
	{
		GLenum format = 0;
		if (nr_components == 1)
			format = GL_RED;
		else if (nr_components == 3)
			format = GL_RGB;
		else if (nr_components == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return texture_id;
}

#endif