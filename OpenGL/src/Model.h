#pragma once
#include <string>
#include "Texture.h"
#include "Shader.h"
#include "glm/gtx/transform.hpp"

class Model {
public:
	std::unique_ptr<float[]>  m_VertexData;
	std::unique_ptr<unsigned int[]>  m_IndexData;
	int m_VertexDataCount;
	int m_IndexDataCount;

	Model(const std::string filePath);
	Model(float* VertexData, int VertexDataCount, unsigned int* IndexData, int IndexDataCount);
	
	//void AddShader(Shader s);
	glm::mat4 GetModelMat() const;

	glm::vec3 m_Pos;
	glm::vec3 m_Rot;
	glm::vec3 m_Scl;
};