#include "Camera.h"
#include "GLFWContext.h"

namespace ComplementEngine {
	void Camera::calculateProjectionMatrix()
	{
		if (m_Perspective) {
			m_ProjectionMatrix = glm::perspective(m_Fov, GLFWContext::getProjectionAspectRatio(), m_NearClip, m_FarClip);
		}
		else {
			m_ProjectionMatrix = glm::ortho(GLFWContext::getProjectionLeftBound(), GLFWContext::getProjectionRightBound(), GLFWContext::getProjectionBottomBound(), GLFWContext::getProjectionUpBound(), m_NearClip, m_FarClip);
		}
	}

	Camera::Camera()
		: m_Perspective(true)
	{
		calculateProjectionMatrix();
	}

	Camera::Camera(bool perspective)
		: m_Perspective(perspective)
	{
		calculateProjectionMatrix();
	}

	Camera::Camera(const CameraTransform transform, bool perspective)
		: transform(transform), m_Perspective(perspective)
	{
		calculateProjectionMatrix();
	}

	void Camera::setProjectionType(bool perspective)
	{
		m_Perspective = perspective;
		calculateProjectionMatrix();
	}

	void Camera::setNearClip(float nearClip)
	{
		m_NearClip = nearClip;
		calculateProjectionMatrix();
	}

	void Camera::setFarClip(float farClip)
	{
		m_FarClip = farClip;
		calculateProjectionMatrix();
	}

	void Camera::setFov(float fov)
	{
		m_Fov = glm::radians(fov);
		calculateProjectionMatrix();
	}

	void Camera::onKeyboardListen() //TODO: REFACTOR
	{
		float translationFactor = GLFWContext::getDeltaTime();

		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			translationFactor *= 5;
		}

		glm::vec3 translationVector = glm::vec3(0.0f, 0.0f, 0.0f);
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
			translationVector += transform.getForwardVector() * translationFactor;
		}
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
			translationVector += transform.getForwardVector() * -translationFactor;
		}
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
			translationVector += transform.getRightVector() * -translationFactor;
		}
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
			translationVector += transform.getRightVector() * translationFactor;
		}

		transform.move(translationVector);

		float rotationFactor = GLFWContext::getDeltaTime() * 20.0f;
		glm::vec3 rotationVector = glm::vec3(0.0, 0.0, 0.0);
		if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			double mouseXDelta = GLFWContext::getDeltaMouseCursorX();
			double mouseYDelta = GLFWContext::getDeltaMouseCursorY();
			rotationVector += glm::vec3(mouseYDelta, mouseXDelta, 0.0) * rotationFactor;
			transform.rotate(rotationVector);
		}
	}
}