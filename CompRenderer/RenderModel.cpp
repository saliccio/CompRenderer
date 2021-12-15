#include "RenderModel.h"

CompRenderer::RenderModel::RenderModel()
{

}

CompRenderer::RenderModel::RenderModel(const std::string& filePath, Transform* entityTransformPtr)
	: m_Model(filePath), m_EntityTransformPtr(entityTransformPtr)
{
	
}

CompRenderer::RenderModel::RenderModel(Model&& model, Transform* entityTransformPtr)
	: m_Model(std::move(model)), m_EntityTransformPtr(entityTransformPtr)
{
	
}

CompRenderer::RenderModel::RenderModel(const RenderModel& other)
	: m_Model(other.m_Model)
{
	*this = other;
}

CompRenderer::RenderModel::~RenderModel()
{
	
}

void CompRenderer::RenderModel::operator=(const RenderModel& other)
{
	m_Model = other.m_Model;
}

void CompRenderer::RenderModel::draw(Renderer& renderer)
{
	assert(m_EntityTransformPtr);

	if (m_LastRendererPtr != &renderer) {
		m_LastRendererPtr = &renderer;
		onRendererChange(m_LastRendererPtr);
	}

	renderer.setBoundTransformPtr(m_EntityTransformPtr);
	std::vector<Mesh*>& meshes = m_Model.getMeshes();
	for (unsigned int i = 0; i < meshes.size(); i++) {
		renderer.draw(meshes[i]);
	}
}

void CompRenderer::RenderModel::draw(Renderer& renderer, glm::mat4& modelMatrix)
{
	if (m_LastRendererPtr != &renderer) {
		m_LastRendererPtr = &renderer;
		onRendererChange(m_LastRendererPtr);
	}

	std::vector<Mesh*>& meshes = m_Model.getMeshes();
	for (unsigned int i = 0; i < meshes.size(); i++) {
		renderer.draw(meshes[i], modelMatrix);
	}
}
