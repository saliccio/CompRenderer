#pragma once
#include "RenderModel.h"

namespace ComplementEngine {
	struct GizmoArrows {
		RenderModel x, y, z;
	};

	class Gizmo {
	private:
		GizmoArrows m_Arrows;
	};
}