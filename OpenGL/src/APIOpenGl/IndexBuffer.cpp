#include <GL/glew.h>
#include "GLErrorManager.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int * data, int count)
	: m_Count(count), m_Data(data)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_READ));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	int t = m_Data[0];
	t = m_Data[1];
	t = m_Data[10];
	t = m_Data[m_Count];
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
