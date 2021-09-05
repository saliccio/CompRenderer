#pragma once
#include <string>
#include "RenderModel.h"

namespace ComplementEngine {

	struct GizmoArrows {
		RenderModel x, y, z;

		GizmoArrows(const std::string& arrowPath)
			: x(arrowPath, nullptr), y(arrowPath, nullptr), z(arrowPath, nullptr)
		{
			
		}
	};

	class Gizmo {
	private:
		GizmoArrows m_Arrows;
		Transform* m_OwnerTransformPtr;
	public:
		Gizmo(Transform& transform);

		void draw(Renderer& renderer);
	};
}