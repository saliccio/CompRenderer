#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include "CameraTransform.h"

namespace ComplementEngine {
	class Camera {
	private:
		bool m_Perspective = true;
		float m_NearClip = -1.0f;
		float m_FarClip = 1.0f;
		float m_Fov = 0.0f;
		glm::mat4 m_ProjectionMatrix; // cached
		//static std::vector<Camera> m_ActiveCamera;
	private:
		void calculateProjectionMatrix();
	public:
		CameraTransform transform;
	public:
		Camera();
		Camera(bool perspective);
		Camera(const CameraTransform& transform, bool perspective);

		void setProjectionType(bool perspective);
		void setNearClip(float nearClip);
		void setFarClip(float farClip);
		void setFov(float fov);

		void onKeyboardListen();

		//static inline const std::vector<Camera>& getActiveCamera() { return m_ActiveCamera; }

		inline const glm::mat4& getViewMatrix() { return transform.getViewMatrix(); }
		inline const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
	};
}