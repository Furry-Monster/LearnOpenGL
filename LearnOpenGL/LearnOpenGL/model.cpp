#include "model.h"

model::model(std::string const& path, bool gamma = false) :gamma_correction_(gamma)
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

mesh model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertex vertex;
		glm::vec3 vector3;
		//process position
		vector3.x = mesh->mVertices[i].x;
		vector3.y = mesh->mVertices[i].y;
		vector3.z = mesh->mVertices[i].z;
		vertex.position = vector3;
		// process normal
		vector3.x = mesh->mNormals[i].x;
		vector3.y = mesh->mNormals[i].y;
		vector3.z = mesh->mNormals[i].z;
		vertex.normal = vector3;
		//process 
		if (mesh->mTextureCoords[0])
		{
			// texture coords
			glm::vec2 vector2;
			vector2.x = mesh->mTextureCoords[0][i].x;
			vector2.y = mesh->mTextureCoords[0][i].y;
			vertex.tex_coords = vector2;

			// tangent
			vector3.x = mesh->mTangents[i].x;
			vector3.y = mesh->mTangents[i].y;
			vector3.z = mesh->mTangents[i].z;
			vertex.tangent = vector3;
			// bitangent
			vector3.x = mesh->mBitangents[i].x;
			vector3.y = mesh->mBitangents[i].y;
			vector3.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector3;
		}
		else
		{
			vertex.tex_coords = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	//process the index
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[i]);
	}

	//process materials
	if (mesh->mMaterialIndex > 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
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
	}

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
		for (unsigned int j = 0; j < textures_loaded_.size(); j++)
		{
			if (std::strcmp(textures[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded_[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			// load texture if not loaded
			texture texture;
			texture.id = texture_from_file(str.C_Str(), directory_, gamma_correction_);
			texture.type = type_name;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded_.push_back(texture);
		}
	}
	return textures;
}