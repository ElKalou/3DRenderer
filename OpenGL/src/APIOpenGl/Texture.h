#pragma once


class Texture {
private:
	unsigned int m_RendererID;
	void * m_LocalBuffer;
	int m_CPP;
	int m_Width, m_Height;
public:
	Texture(const std::string& filePath);
	~Texture();
	void Bind(unsigned int slot) const;
	void Unbind() const;
};