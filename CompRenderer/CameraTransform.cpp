#include "CameraTransform.h"

namespace CompRenderer {
	void CameraTransform::calculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f));
		onViewMatrixChange(m_ViewMatrix);
	}

	CameraTransform::CameraTransform()
		: m_ViewMatrix(glm::lookAt(m_Position, m_Position + m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)))
	{
		glm::vec3 initialRotation(0.0f, -90.0f, 0.0f);
		rotate(initialRotation);
	}

	void CameraTransform::move(const glm::vec3& movementVector)
	{
		Transform::move(movementVector);
	
		calculateViewMatrix();
	}

	void CameraTransform::rotate(glm::vec3& rotationVector)
	{
		float totalNewXRotation = m_Rotation.x + rotationVector.x;

		if (totalNewXRotation > 89.0f) {
			rotationVector.x = 89.0f - m_Rotation.x;
		}

		if (totalNewXRotation < -89.0f) {
			rotationVector.x = -89.0f - m_Rotation.x;
		}

		Transform::rotate(rotationVector);

		calculateViewMatrix();
	}

	void CameraTransform::scale(const glm::vec3 scaleVector)
	{
		Transform::scale(scaleVector);
		calculateViewMatrix();
	}

	void CameraTransform::setPosition(const glm::vec3 positionVector)
	{
		Transform::setPosition(positionVector);
		calculateViewMatrix();
	}

	void CameraTransform::setRotation(glm::vec3& rotationVector)
	{
		if (rotationVector.x > 89.0f) {
			rotationVector.x = 89.0f;
		}

		if (rotationVector.x < -89.0f) {
			rotationVector.x = -89.0f;
		}

		Transform::setRotation(rotationVector);

		calculateViewMatrix();
	}

	/*void CameraTransform::setRotation(const glm::quat quaternion)
	{
		Transform::setRotation(quaternion);
		calculateViewMatrix();
	}*/

	void CameraTransform::setScale(const glm::vec3 scaleVector)
	{
		Transform::setScale(scaleVector);
		calculateViewMatrix();
	}
}