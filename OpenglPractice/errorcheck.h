#pragma once
#include <iostream>

inline void glClearErrors() {
	while (glGetError() != GL_NO_ERROR) {
		std::cout << glGetError() << std::endl;
	}
}

inline bool glLogError(char const* file, char const* function, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[ERROR: " << error << "] File: " << file << " Function: " << function << " Line: " << line << std::endl;
		return false;
	}
	return true;
}

#define ASSERT(x) if(!(x)) __debugbreak()

#define E(x) glClearErrors();\
	x;\
	ASSERT(glLogError(__FILE__, #x, __LINE__))