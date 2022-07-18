#include "VertexArray.hpp"

namespace Moon
{
	VertexArray::VertexArray() : m_IndexBuffer(nullptr)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::SetIBO(IndexBuffer* ibo)
	{
		m_IndexBuffer = ibo;
	}

	void VertexArray::AddVBO(VertexBuffer* vbo)
	{
		Bind();
		vbo->GetBuffer()->Bind();
		Int location = vbo->GetLocation();
		Int size = vbo->GetSize();
		Int stride = vbo->GetStride();
		Int64 pointer = vbo->GetPointer();
		glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
		glEnableVertexAttribArray(location);
		vbo->GetBuffer()->Unbind();
		Unbind();
	}

	void VertexArray::Render()
	{
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
	}
}