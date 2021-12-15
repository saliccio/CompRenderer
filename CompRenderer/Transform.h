#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <Events/EventDispatcher.h>

namespace CompRenderer {
	class Transform {
	protected:
		glm::mat4 m_ModelMatrix; // caching
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_ForwardVector;
		glm::vec3 m_RightVector;
		glm::vec3 m_UpVector;
		glm::vec3 m_Rotation;
	public:
		EventDispatcher <void, const glm::vec3&> onPositionChange;
		EventDispatcher <void, const glm::vec3&> onRotationChange;
		EventDispatcher <void, const glm::vec3&> onScaleChange;
		EventDispatcher <void, const glm::mat4&> onModelMatrixChange;

		Transform();

		virtual void move(const glm::vec3& movementVector);
		virtual void rotate(glm::vec3& rotationAxis);
		//virtual void rotate(const glm::quat& quaternion);
		virtual void scale(const glm::vec3 scaleVector);

		virtual void setPosition(const glm::vec3 positionVector);
		virtual void setRotation(glm::vec3& rotationVector);
		//virtual void setRotation(const glm::quat quaternion);
		virtual void setScale(const glm::vec3 scaleVector);

		inline const glm::vec3& getPosition() const { return m_Position; }
		inline const glm::vec4 getPosition4f() const { return glm::vec4(m_Position.x, m_Position.y, m_Position.z, 1.0f); }
		inline const glm::vec3& getRotation() const { return m_Rotation; }
		inline const glm::vec3& getScale() const { return m_Scale; }
		inline const glm::mat4& getModelMatrix() const { return m_ModelMatrix; }
		inline const glm::vec3& getForwardVector() const { return m_ForwardVector; }
		inline const glm::vec4& getForwardVector4f() const { return glm::vec4(m_ForwardVector.x, m_ForwardVector.y, m_ForwardVector.z, 0.0f); }
		inline const glm::vec3& getRightVector() const { return m_RightVector; }
	};
}