#include "Model.h"
#include <iostream>
#include "obj_loader/OBJ_Loader.h"


Model::Model(const std::string objPath) :
	m_Pos(0.0f), m_Rot(0.0f), m_Scl(1.0f)
{
	objl::Loader Loader;
	if (!Loader.LoadFile(objPath.c_str())) {
		std::cout << "Could not load file " << objPath << std::endl;
	}

	m_VertexDataCount = Loader.LoadedVertices.size() * (3 + 2 + 3);
	
	m_VertexData = std::make_unique<float[]>(m_VertexDataCount);
	int currentPos = 0;
	for (auto vert : Loader.LoadedVertices) {
		m_VertexData[currentPos] = vert.Position.X;
		m_VertexData[currentPos + 1] = vert.Position.Y;
		m_VertexData[currentPos + 2] = vert.Position.Z;
		m_VertexData[currentPos + 3] = vert.TextureCoordinate.X;
		m_VertexData[currentPos + 4] = vert.TextureCoordinate.Y;
		m_VertexData[currentPos + 5] = vert.Normal.X;
		m_VertexData[currentPos + 6] = vert.Normal.Y;
		m_VertexData[currentPos + 7] = vert.Normal.Z;
		currentPos += 8;
	}

	m_IndexDataCount = Loader.LoadedIndices.size();
	m_IndexData = std::make_unique<unsigned int[]>(m_IndexDataCount);

	for (int i = 0; i < m_IndexDataCount; i++)
	{
		m_IndexData[i] = Loader.LoadedIndices[i];
	}
}

Model::Model(float * VertexData, int VertexDataCount, unsigned int * IndexData, int IndexDataCount) :
	m_VertexData(VertexData), m_IndexData(IndexData), m_VertexDataCount(VertexDataCount),
	m_IndexDataCount(IndexDataCount)
{
}

glm::mat4 Model::GetModelMat() const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Pos);
	model = glm::rotate(model, glm::radians(m_Rot[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rot[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rot[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, m_Scl);
	return model;
}
