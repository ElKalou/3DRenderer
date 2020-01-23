#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "GL/glew.h"
#include "GLErrorManager.h"
#include "Texture.h"


Texture::Texture(const std::string& filePath)
	: m_RendererID(0), m_Width(0), m_Height(0), m_CPP(0), m_LocalBuffer(nullptr)
{
	GLCall(glGenTextures(1, &m_RendererID));

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_CPP, 0);
	if (!m_LocalBuffer)
		std::cout << "Could not load texture file: " << filePath.c_str() << std::endl;

	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	switch (m_CPP)
	{
		case 3:
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
			break;
		case 4:
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
			break;
		default:
			break;
	}
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
