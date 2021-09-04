#pragma once
#include <vector>
#include "Component.h"

namespace ComplementEngine {
	class Object {
	private:
		std::vector<Component> m_Components;
	};
}