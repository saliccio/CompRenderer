#pragma once
#include <GLFW/glfw3.h>

namespace CompRenderer {
	class GLFWContext {
	private:
		static float deltaTime;

		static double deltaMouseCursorX;
		static double deltaMouseCursorY;

		static float projectionAspectRatio;

		static float projectionLeftBound;
		static float projectionRightBound;
		static float projectionBottomBound;
		static float projectionUpBound;

		static GLFWwindow* singleton;

		GLFWContext();
	public:
		inline static float getDeltaTime() { return deltaTime; }
		inline static void setDeltaTime(float value) { deltaTime = value; }

		inline static double getDeltaMouseCursorX() { return deltaMouseCursorX; }
		inline static void setDeltaMouseCursorX(double value) { deltaMouseCursorX = value; }

		inline static double getDeltaMouseCursorY() { return deltaMouseCursorY; }
		inline static void setDeltaMouseCursorY(double value) { deltaMouseCursorY = value; }

		inline static float getProjectionAspectRatio() { return projectionAspectRatio; }
		inline static void setProjectionAspectRatio(float value) { projectionAspectRatio = value; }

		inline static float getProjectionLeftBound() { return projectionLeftBound; }
		inline static void setProjectionLeftBound(float value) { projectionLeftBound = value; }

		inline static float getProjectionRightBound() { return projectionRightBound; }
		inline static void setProjectionRightBound(float value) { projectionRightBound = value; }

		inline static float getProjectionBottomBound() { return projectionBottomBound; }
		inline static void setProjectionBottomBound(float value) { projectionBottomBound = value; }

		inline static float getProjectionUpBound() { return projectionUpBound; }
		inline static void setProjectionUpBound(float value) { projectionUpBound = value; }


		inline static GLFWwindow* const getInstance() { return singleton; }
		inline static void setInstance(GLFWwindow* window) { singleton = window; }
	};
}