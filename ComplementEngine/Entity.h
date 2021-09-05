#pragma once
#include <string>
#include <unordered_map>
#include <typeindex>
#include "Model.h"
#include "Component.h"
#include "RenderModel.h"
#include "Gizmo.h"

namespace ComplementEngine {
	class Entity {
	private:
		unsigned int m_ID;
		std::string m_Name;
		std::unordered_map<std::type_index, Component> m_Components;
		Gizmo m_Gizmo;
	private:
		static unsigned int generateID();
	public:
		Transform transform;
		RenderModel renderComponent;
	public:
		Entity(const std::string& name);
		Entity(const std::string& name, const std::string& modelFilePath);
		Entity(const std::string& name, Model& model);
		Entity(const Entity& other);
		~Entity();

		void operator =(const Entity& other);
		bool operator ==(const Entity& other);

		template <typename T>
		void addComponent() {
			std::type_index typeIndex = typeid(T);
			static_assert(std::is_base_of<Component, T> && typeid(RenderModel) != typeIndex, "Add Component Invalid Type");
			m_Components[typeIndex] = T();
		}

		template <typename T>
		T& getComponent() {
			std::type_index typeIndex = typeid(T);
			static_assert(std::is_base_of<Component, T> && typeid(RenderModel) != typeIndex, "Get Component Invalid Type");			
			if (m_Components.find(typeIndex) != m_Components.end()) {
				return m_Components[typeIndex];
			} else {
				assert(false);
			}
		}

		void draw(Renderer& renderer);
	};
}