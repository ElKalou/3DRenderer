#pragma once


class IndexBuffer {
private: 
	unsigned int m_RendererID;
	int m_Count;
	const unsigned int* m_Data;
public:
	IndexBuffer(const unsigned int* data, int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	inline int GetCount() const {
		return m_Count;
	}
};

