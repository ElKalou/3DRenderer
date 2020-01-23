#include "VertexArray.h"
#include "GLErrorManager.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	int offset = 0;
	for (int i = 0; i < layout.GetNumberOfAttrib(); i++)
	{
		VertexAttribLayout attrib = layout.GetAttribLayout(i);
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, layout.GetStride(), (const void*) offset));
		offset += attrib.count * attrib.GetSizeFromType(attrib.type);  
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

