#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Shader.h"
#include "GLErrorManager.h"

Shader::Shader(const std::string& filePath)
{
	ShaderProgramSource shaderSource = ParseShader(filePath);
	m_RendererID = CreateShader(shaderSource.vertexShader, shaderSource.fragmentShader);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));

	if (loc < 0)
		std::cout << "Uniform " + name + " does not exist" << std::endl;

	m_UniformLocationCache[name] = loc;
	return loc;
}

void Shader::SetUniform4f(const std::string& uniformName, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(GetUniformLocation(uniformName), f0, f1, f2, f3));
}

void Shader::SetUniform1i(const std::string & uniformName, int value)
{
	GLCall(glUniform1i(GetUniformLocation(uniformName), value));
}

void Shader::SetUniformMat4f(const std::string & uniformName, glm::mat4 matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]));
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath) {
	std::ifstream stream(filePath);

	enum ShaderType { NONE = -1, VERTEX, FRAGMENT };

	ShaderType shaderType = NONE;
	std::stringstream out[2];
	std::string line;
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				shaderType = VERTEX;
			else if (line.find("fragment") != std::string::npos)
				shaderType = FRAGMENT;
		}
		else {
			out[(int)shaderType] << line << "\n";
		}
	}
	return { out[0].str(), out[1].str() };
}

unsigned int Shader::CompileShader(GLenum type, const std::string& source) {
	unsigned int id;
	GLCall(id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, NULL));
	GLCall(glCompileShader(id));

	int shader_compiled;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &shader_compiled));
	if (shader_compiled != GL_TRUE) {
		int length = 0;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(sizeof(char) * length);
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex " : "Fragment ") << "shader did not compile"
			<< std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int programID;
	GLCall(programID = glCreateProgram());
	unsigned int vShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(programID, vShader));
	GLCall(glAttachShader(programID, fShader));
	GLCall(glLinkProgram(programID));

	int linkedProgram;
	GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &linkedProgram));
	if (linkedProgram != GL_TRUE) {
		int length = 0;
		GLCall(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetProgramInfoLog(programID, length, &length, message));
		std::cout << "Program did not linked" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(vShader));
		GLCall(glDeleteShader(fShader));
		return -1;
	}

	GLCall(glValidateProgram(programID));
	GLCall(glDeleteShader(vShader));
	GLCall(glDeleteShader(fShader));
	return programID;
}
