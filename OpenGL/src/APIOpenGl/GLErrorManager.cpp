#include <iostream>
#include <GL/glew.h>

#include "GLErrorManager.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[GL error] :" << error << " in file " << file << " function: " << function <<
			" at line " << line << std::endl;
		return false;
	}
	return true;
} 