#include "RenderModel.h"

ComplementEngine::RenderModel::RenderModel()
{

}

ComplementEngine::RenderModel::RenderModel(const std::string& filePath)
	: m_Model(filePath)
{
	
}

ComplementEngine::RenderModel::RenderModel(Model&& model)
	: m_Model(std::move(model))
{
	
}

ComplementEngine::RenderModel::RenderModel(const RenderModel& other)
	: m_Model(other.m_Model)
{
	*this = other;
}

ComplementEngine::RenderModel::~RenderModel()
{
	
}

void ComplementEngine::RenderModel::operator=(const RenderModel& other)
{
	m_Model = other.m_Model;
}

void ComplementEngine::RenderModel::draw(Renderer& renderer, Transform& transform)
{
	renderer.setBoundTransformPtr(&transform);
	std::vector<Mesh*>& meshes = m_Model.getMeshes();
	for (unsigned int i = 0; i < meshes.size(); i++) {
		renderer.draw(meshes[i]);
	}
}