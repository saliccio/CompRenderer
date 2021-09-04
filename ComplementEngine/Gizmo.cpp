#include "Gizmo.h"

void ComplementEngine::Gizmo::calculateModelMatrix(const glm::vec3& dummy)
{
	//m_CachedModelMatrix = glm::translate(glm::identity<glm::mat4>(), newOwnerPosition);
}

ComplementEngine::Gizmo::Gizmo(Transform& transform, CameraTransform& cameraTransform)
	: m_Arrows("arrow.fbx"), m_OwnerTransformPtr(&transform), m_CachedModelMatrix(m_OwnerTransformPtr->getModelMatrix())					// VOLATILE - ARROW
{
	transform.onPositionChange += [&](const glm::vec3& newTransform) { calculateModelMatrix(newTransform); };
	//cameraTransform.onViewMatrixChange += [&](const glm::mat4& newMatrix) { alignToOwnerTransform(newTransform); };
}
