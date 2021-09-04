#include <iostream>
#include <GL/glew.h>
#include "errorcheck.h"

/*void glClearErrors() {
	while (glGetError() != GL_NO_ERROR) {
		std::cout << glGetError() << std::endl;
	}
}

bool glLogError(char const* file, char const* function, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[ERROR: " << error << "] File: " << file << " Function: " << function << " Line: " << line << std::endl;
		return false;
	}
	return true;
}*/