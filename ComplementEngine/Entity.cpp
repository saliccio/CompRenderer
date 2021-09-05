#include "Entity.h"

unsigned int ComplementEngine::Entity::generateID()
{
	static unsigned int s_ID = 1;
	return s_ID++;
}

ComplementEngine::Entity::Entity(const std::string& name)
	: m_ID(generateID()), m_Name(name), m_Gizmo(transform)
{

}


ComplementEngine::Entity::Entity(const std::string& name, const std::string& modelFilePath)
	: m_ID(generateID()), m_Name(name), renderComponent(modelFilePath, &transform), m_Gizmo(transform)
{
	
}

ComplementEngine::Entity::Entity(const std::string& name, Model& model)
	: m_ID(generateID()), m_Name(name), renderComponent(std::move(model), &transform), m_Gizmo(transform)
{
	
}

ComplementEngine::Entity::Entity(const Entity& other)
	: m_Gizmo(transform)
{
	*this = other;
}

ComplementEngine::Entity::~Entity()
{

}

void ComplementEngine::Entity::operator=(const Entity& other)
{
	*this = other;
}

bool ComplementEngine::Entity::operator==(const Entity& other)
{
	return m_ID == other.m_ID;
}

void ComplementEngine::Entity::draw(Renderer& renderer)
{
	renderComponent.draw(renderer);

	m_Gizmo.draw(renderer);
}
