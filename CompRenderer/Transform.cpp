#include "Transform.h"
#include <iostream>

namespace CompRenderer {
	Transform::Transform()
		: m_Position(glm::vec3(0.0, 0.0, 0.0)), m_Scale(glm::vec3(1.0, 1.0, 1.0)),
		m_Rotation(glm::vec3(0, 0, 0)), m_ForwardVector(0.0f, 0.0f, 1.0f), m_RightVector(1.0f, 0.0f, 0.0f), m_UpVector(0.0f, 1.0f, 0.0f)
	{
		glm::mat4 identityMat4(1.0);
		m_ModelMatrix = glm::translate(identityMat4, m_Position) * glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z) * glm::scale(identityMat4, m_Scale);
	}

	void Transform::move(const glm::vec3& movementVector)
	{
		m_Position += movementVector;
		m_ModelMatrix = glm::translate(m_ModelMatrix, movementVector);
		onPositionChange(m_Position);
		onModelMatrixChange(m_ModelMatrix);
	}

	void Transform::rotate(glm::vec3& rotationVector)
	{
		// x -> pitch
		// y -> yaw
		// z -> roll

		m_Rotation.x += rotationVector.x;
		m_Rotation.y += rotationVector.y;
		m_Rotation.z += rotationVector.z;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		direction.y = sin(glm::radians(m_Rotation.x));
		direction.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));

		m_ForwardVector = glm::normalize(direction);

		m_RightVector = glm::normalize(glm::cross(m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

		m_UpVector = glm::normalize(glm::cross(m_RightVector, m_ForwardVector));

		m_ModelMatrix = glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z) * m_ModelMatrix;
		onRotationChange(rotationVector);
		onModelMatrixChange(m_ModelMatrix);
	}

	/*void Transform::rotate(const glm::quat& rotationQuaternion)
	{
		static float s_Pitch = 0, s_Yaw = 0;

		glm::vec3 rotationVector = glm::eulerAngles(rotationQuaternion);

		s_Pitch += rotationVector.x;
		s_Yaw += rotationVector.y;

		if (s_Pitch > 89.0f) {
			s_Pitch = 89.0f;
		}

		if (s_Pitch < -89.0f) {
			s_Pitch = -89.0f;
		}

		glm::vec3 direction;
		direction.x = cos(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));
		direction.y = sin(glm::radians(s_Pitch));
		direction.z = sin(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));

		m_ForwardVector = glm::normalize(direction);

		m_RightVector = glm::normalize(glm::cross(m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

		m_Rotation = rotationQuaternion * m_Rotation; // may be wrong
		m_ModelMatrix = glm::toMat4(m_Rotation) * m_ModelMatrix;
		onRotationChange(rotationVector);
	}*/

	void Transform::scale(const glm::vec3 scaleVector)
	{
		m_Scale += scaleVector;
		m_ModelMatrix = glm::scale(glm::mat4(1.0), m_Scale) * m_ModelMatrix;
		onScaleChange(m_Scale);
		onModelMatrixChange(m_ModelMatrix);
	}

	void Transform::setPosition(const glm::vec3 movementVector)
	{
		m_ModelMatrix = glm::inverse(glm::translate(glm::mat4(1.0), m_Position)) * m_ModelMatrix; // may be wrong
		m_Position = movementVector;
		m_ModelMatrix = glm::translate(glm::mat4(1.0), movementVector) * m_ModelMatrix;
		onPositionChange(m_Position);
		onModelMatrixChange(m_ModelMatrix);
	}

	void Transform::setRotation(glm::vec3& rotationVector)
	{
		m_Rotation.x += rotationVector.x;
		m_Rotation.y += rotationVector.y;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		direction.y = sin(glm::radians(m_Rotation.x));
		direction.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));

		m_ForwardVector = glm::normalize(direction);

		m_RightVector = glm::normalize(glm::cross(m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

		m_UpVector = glm::normalize(glm::cross(m_RightVector, m_ForwardVector));

		rotationVector.x = glm::radians(rotationVector.x);
		rotationVector.y = glm::radians(rotationVector.y);
		rotationVector.z = glm::radians(rotationVector.z);


		m_ModelMatrix = glm::inverse(glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z)) * m_ModelMatrix; // may be wrong
		
		m_Rotation = rotationVector;
		
		m_ModelMatrix = glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z) * m_ModelMatrix;
		
		onRotationChange(rotationVector);
		onModelMatrixChange(m_ModelMatrix);
	}

	/*void Transform::setRotation(const glm::quat rotationQuaternion)
	{
		static float s_Pitch = 0, s_Yaw = 0;

		glm::vec3 rotationVector = glm::eulerAngles(rotationQuaternion);

		s_Pitch += rotationVector.x;
		s_Yaw += rotationVector.y;

		if (s_Pitch > 89.0f) {
			s_Pitch = 89.0f;
		}

		if (s_Pitch < -89.0f) {
			s_Pitch = -89.0f;
		}

		glm::vec3 direction;
		direction.x = cos(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));
		direction.y = sin(glm::radians(s_Pitch));
		direction.z = sin(glm::radians(s_Yaw)) * cos(glm::radians(s_Pitch));

		m_ForwardVector = glm::normalize(direction);

		m_RightVector = glm::normalize(glm::cross(m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f)));

		m_ModelMatrix = glm::inverse(glm::toMat4(m_Rotation)) * m_ModelMatrix; // may be wrong
		m_Rotation = rotationQuaternion;
		m_ModelMatrix = glm::toMat4(m_Rotation) * m_ModelMatrix;
		onRotationChange(rotationVector);
	}*/

	void Transform::setScale(const glm::vec3 scaleVector)
	{
		m_ModelMatrix = glm::inverse(glm::scale(glm::mat4(1.0), m_Scale)) * m_ModelMatrix; // may be wrong
		m_Scale = scaleVector;
		m_ModelMatrix = glm::scale(glm::mat4(1.0), m_Scale) * m_ModelMatrix;
		onScaleChange(scaleVector);
		onModelMatrixChange(m_ModelMatrix);
	}
}