#pragma once
#include <GL/glew.h>


class VertexBuffer {
private:
	unsigned int m_RendererID;
	const void* m_Data;
public:
	VertexBuffer(const void* data, int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};

