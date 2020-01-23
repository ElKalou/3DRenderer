#pragma once

#define Assert(x, b) if(x != b) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	Assert(GLLogCall(#x, __FILE__, __LINE__), true);\

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

