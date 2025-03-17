#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec.hpp>

class shader
{
public:
	unsigned int id;

	shader(const char* vertex_path, const char* fragment_path);
	~shader();

	void use() const;

	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;

	void set_vec2(const std::string& name, const glm::vec2& value) const;
	void set_vec2(const std::string& name, float x, float y)const;
	void set_vec3(const std::string& name, const glm::vec3& value) const;
	void set_vec3(const std::string& name, float x, float y, float z)const;
	void set_vec4(const std::string& name, const glm::vec4& value) const;
	void set_vec4(const std::string& name, float x, float y, float z, float w)const;

	void set_mat2(const std::string& name, const glm::mat2& value) const;
	void set_mat3(const std::string& name, const glm::mat3& value) const;
	void set_mat4(const std::string& name, const glm::mat4& value) const;

};

#endif // SHADER_H