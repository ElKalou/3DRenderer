#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
	
};

class Shader {
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filePath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	int GetUniformLocation(const std::string& uniform);
	void SetUniform4f(const std::string& uniform, float f0, float f1, float f2, float f3);
	void SetUniform1i(const std::string& uniform, int value);
	void SetUniformMat4f(const std::string& uniformName, glm::mat4 matrix);

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(GLenum type, const std::string& source);
};