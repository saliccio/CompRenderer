#include "GLFWContext.h"

namespace CompRenderer {
	float GLFWContext::deltaTime = 0.0f;

	double GLFWContext::deltaMouseCursorX = 0.0;
	double GLFWContext::deltaMouseCursorY = 0.0;

	float GLFWContext::projectionAspectRatio = 4.0f / 3.0f;

	float GLFWContext::projectionLeftBound = -1.0f;
	float GLFWContext::projectionRightBound = 1.0f;
	float GLFWContext::projectionBottomBound = -1.0f;
	float GLFWContext::projectionUpBound = 1.0f;

	GLFWwindow* GLFWContext::singleton;
}