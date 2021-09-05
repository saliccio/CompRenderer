#include <glm/gtx/norm.hpp>
#include "Gizmo.h"

ComplementEngine::Gizmo::Gizmo(Transform& ownerTransform)
	: m_Arrows("arrow.fbx"), m_OwnerTransformPtr(&ownerTransform)		// VOLATILE - ARROW
{
	
}

void ComplementEngine::Gizmo::draw(Renderer& renderer)
{
	glm::mat4 modelMatrix = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.1f, 0.1f, 1.0f));
	
	glm::vec3 ownerRotation = m_OwnerTransformPtr->getRotation();
	modelMatrix = glm::eulerAngleXYZ(ownerRotation.x, ownerRotation.y, ownerRotation.z) * modelMatrix;
	
	modelMatrix = glm::translate(modelMatrix, m_OwnerTransformPtr->getPosition());

	m_Arrows.x.draw(renderer, modelMatrix);
	m_Arrows.y.draw(renderer, modelMatrix);
	m_Arrows.z.draw(renderer, modelMatrix);
}
