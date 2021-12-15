#pragma once
#include <GL/glew.h>
#include <vector>
#include "errorcheck.h"

namespace CompRenderer {
	class IndexBuffer {
	private:
		unsigned int m_ID;
		unsigned int m_Size;
	public:
		explicit IndexBuffer(const std::vector<unsigned int>& data);
		IndexBuffer(const unsigned int* data, unsigned int size);
		~IndexBuffer();

		void bind() const;
		static void unbind();
		inline unsigned int getCount() const { return m_Size; };
	};
}