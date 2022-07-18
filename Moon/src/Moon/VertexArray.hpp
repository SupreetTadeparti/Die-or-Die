#pragma once

#include "Core.h"
#include "Buffer.hpp"
#include "Shader.hpp"

namespace Moon
{
	class MOON_API VertexArray
	{
	public:
		VertexArray();
		
		void AddVBO(VertexBuffer* vbo);
		void SetIBO(IndexBuffer* ibo);

		void Render();

		inline IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; };

		inline void Bind() const { glBindVertexArray(m_VertexArrayID); };
		inline void Unbind() const { glBindVertexArray(0); };
	private:
		Uint m_VertexArrayID;
		IndexBuffer* m_IndexBuffer;
	};
}