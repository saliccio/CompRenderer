#pragma once
#include "Component.h"
#include "Model.h"
#include "CGE_Events/EventDispatcher.h"

namespace ComplementEngine {
	class RenderModel : public Component {
	private:
		Model m_Model;
		Renderer* m_LastRendererPtr;		// CURRENTLY OBSOLOTE
		Transform* m_EntityTransformPtr;
	public:
		RenderModel();
		RenderModel(const std::string& filePath, Transform* entityTransformPtr);
		RenderModel(Model&& model, Transform* entityTransformPtr);
		RenderModel(const RenderModel& other);
		~RenderModel();

		EventDispatcher<void, Renderer*> onRendererChange;

		void operator =(const RenderModel& other);

		inline Renderer* getRenderer() { return m_LastRendererPtr; }
		inline Model getModel() { return m_Model; };
		inline void setModel(Model&& model) {
			m_Model = std::move(model);
		};

		void draw(Renderer& renderer);
		void draw(Renderer& renderer, glm::mat4& modelMatrix);
	};
}