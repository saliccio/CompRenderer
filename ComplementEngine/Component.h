#pragma once

namespace ComplementEngine {
	class Component {
	protected:
		unsigned int m_ID;

	protected:
		static unsigned int generateID();
	public:
		inline unsigned int getID() const { return m_ID; };

		bool operator ==(const Component& other);
	};
}