#include "model.h"

model::model(const char* path, const bool gamma) :gamma_correction_(gamma)
{
	load_model(path);
}

void model::draw(const shader& shader) const
{
	for (const auto& mesh : meshes_)
		mesh.draw(shader);
}

void model::load_model(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
		return;
	}

	directory_ = path.substr(0, path.find_last_of('/'));

	process_node(scene->mRootNode, scene);
}

void model::process_node(const aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(process_mesh(mesh, scene));
	}

	for (unsigned int j = 0; j < node->mNumChildren; j++)
	{
		process_node(node->mChildren[j], scene);
	}
}

mesh model::process_mesh(aiMesh* mesh_in, const aiScene* scene)
{
	// data to fill
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;

	// walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh_in->mNumVertices; i++)
	{
		vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh_in->mVertices[i].x;
		vector.y = mesh_in->mVertices[i].y;
		vector.z = mesh_in->mVertices[i].z;
		vertex.position = vector;
		// normals
		if (mesh_in->HasNormals())
		{
			vector.x = mesh_in->mNormals[i].x;
			vector.y = mesh_in->mNormals[i].y;
			vector.z = mesh_in->mNormals[i].z;
			vertex.normal = vector;
		}
		// texture coordinates
		if (mesh_in->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh_in->mTextureCoords[0][i].x;
			vec.y = mesh_in->mTextureCoords[0][i].y;
			vertex.tex_coords = vec;
		}
		else {
			vertex.tex_coords = glm::vec2(0.0f, 0.0f);
		}
		if (mesh_in->HasTangentsAndBitangents())
		{
			// tangent
			vector.x = mesh_in->mTangents[i].x;
			vector.y = mesh_in->mTangents[i].y;
			vector.z = mesh_in->mTangents[i].z;
			vertex.tangent = vector;
			// bitangent
			vector.x = mesh_in->mBitangents[i].x;
			vector.y = mesh_in->mBitangents[i].y;
			vector.z = mesh_in->mBitangents[i].z;
			vertex.bitangent = vector;
		}
		else
		{
			vertex.tangent = glm::vec3(0.0f, 0.0f, 0.0f);
			vertex.bitangent = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh_in->mNumFaces; i++)
	{
		aiFace face = mesh_in->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh_in->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
	// 2. specular maps
	std::vector<texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
	// 3. normal maps
	std::vector<texture> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
	// 4. height maps
	std::vector<texture> height_maps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), height_maps.begin(), height_maps.end());

	// return a mesh object created from the extracted mesh data
	return mesh(vertices, indices, textures);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<texture> model::load_material_textures(const aiMaterial* material, const aiTextureType type, const std::string& type_name)
{
	std::vector<texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (auto& loaded_texture : textures_loaded_)
		{
			if (std::strcmp(loaded_texture.path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(loaded_texture);
				skip = true;
				break;
			}
		}
		if (!skip) {
			// load texture if not loaded
			texture texture;
			texture.id = texture_from_file(str.C_Str(), directory_, gamma_correction_);
			texture.type = type_name;
			texture.path = str;
			textures.push_back(texture);
			textures_loaded_.push_back(texture);
		}
	}
	return textures;
}