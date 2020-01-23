#pragma once

#include <vector>
#include <GLFW/glfw3.h>

struct VertexAttribLayout {
	unsigned int count;
	unsigned int type;
	unsigned int normalized;

	inline int GetSizeFromType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_INT: return 4;
			case GL_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexAttribLayout> m_AttribLayouts;
	int m_Stride;
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	inline void AddAttribute(unsigned int count) 
	{ 
		static_assert(false); 
	}

	template<>
	inline void AddAttribute<unsigned int>(unsigned int count) {
		m_AttribLayouts.push_back({ count, GL_INT, GL_FALSE });
		m_Stride += count * 4;
	}

	template<>
	inline void AddAttribute<float>(unsigned int count) {
		m_AttribLayouts.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += count * 4;
	}

	template<>
	inline void AddAttribute<char>(unsigned int count) {
		m_AttribLayouts.push_back({ count, GL_BYTE, GL_TRUE });
		m_Stride += count;
	}

	inline int GetNumberOfAttrib() const {
		return (int)m_AttribLayouts.size();
	}

	inline const VertexAttribLayout GetAttribLayout(int index) const {
		return m_AttribLayouts[index];
	}

	inline int GetStride() const {
		return m_Stride;
	}

};


