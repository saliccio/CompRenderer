#include <Entity.h>

unsigned int CompRenderer::Entity::generateID()
{
	static unsigned int s_ID = 1;
	return s_ID++;
}


CompRenderer::Entity::Entity(const std::string& name)
	: m_ID(generateID()), m_Name(name)
{
	
}


CompRenderer::Entity::Entity(const std::string& name, const std::string& modelFilePath)
	: m_ID(generateID()), m_Name(name), renderComponent(modelFilePath, &transform)
{
	
}

CompRenderer::Entity::Entity(const std::string& name, Model& model)
	: m_ID(generateID()), m_Name(name), renderComponent(std::move(model), &transform)
{
	
}

CompRenderer::Entity::Entity(const Entity& other)
{
	*this = other;
}

CompRenderer::Entity::~Entity()
{

}

bool CompRenderer::Entity::operator==(const Entity& other)
{
	return m_ID == other.m_ID;
}

void CompRenderer::Entity::draw(Renderer& renderer)
{
	renderComponent.draw(renderer);
}
