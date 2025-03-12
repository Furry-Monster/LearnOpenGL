#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
};

#endif // SHADER_H