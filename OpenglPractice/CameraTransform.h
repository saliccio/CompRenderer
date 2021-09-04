#pragma once
#include "Transform.h"

namespace ComplementEngine {
	class CameraTransform : public Transform {
	private:
		glm::mat4 m_ViewMatrix;

		void calculateViewMatrix();
	public:
		EventDispatcher<void, const glm::mat4&> onViewMatrixChange;

		CameraTransform();

		void move(const glm::vec3& movementVector) override;
		void rotate(glm::vec3& rotationAxis) override;
		//void rotate(const glm::quat& quaternion) override;
		void scale(const glm::vec3 scaleVector) override;

		void setPosition(const glm::vec3 positionVector) override;
		void setRotation(glm::vec3& rotationVector) override;
		//void setRotation(const glm::quat quaternion) override;
		void setScale(const glm::vec3 scaleVector) override;

		inline const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
	};
}