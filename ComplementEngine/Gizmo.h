#pragma once
#include <string>
#include "RenderModel.h"

namespace ComplementEngine {

	struct GizmoArrows {
		RenderModel x, y, z;

		GizmoArrows(const std::string& arrowPath)
			: x(arrowPath), y(arrowPath), z(arrowPath)
		{
			
		}
	};

	class Gizmo {
	private:
		GizmoArrows m_Arrows;
		Transform* m_OwnerTransformPtr;
		glm::mat4 m_CachedModelMatrix;

		void calculateModelMatrix(const glm::vec3& newOwnerPosition);
	public:
		Gizmo(Transform& transform, CameraTransform& cameraTransform);
	};
}