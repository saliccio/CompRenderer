#pragma once
#include "Component.h"
#include "Model.h"

namespace ComplementEngine {
	class RenderModel : public Component {
	private:
		Model m_Model;
	public:
		RenderModel();
		RenderModel(const std::string& filePath);
		RenderModel(Model&& model);
		RenderModel(const RenderModel& other);
		~RenderModel();

		void operator =(const RenderModel& other);

		inline Model getModel() { return m_Model; };
		inline void setModel(Model&& model) {
			m_Model = std::move(model);
		};

		void draw(Renderer& renderer, Transform& transform);
	};
}