#include "Buffer.hpp"

namespace Moon
{
	VertexBuffer::VertexBuffer(int location, int size, int stride, int pointer, Buffer* buffer)
	{
		m_Location = location;
		m_Size = size;
		m_Stride = stride;
		m_Pointer = pointer;
		m_Buffer = buffer;
	}

	template <typename T>
	MOON_API Buffer::Buffer(T* data, Uint count)
	{
		glGenBuffers(1, &m_BufferID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
		Unbind();
	}

	template <typename T>
	MOON_API IndexBuffer::IndexBuffer(T* data, Uint count) : m_Count(count)
	{
		glGenBuffers(1, &m_BufferID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
		Unbind();
	}

	template MOON_API Buffer::Buffer(Double* data, Uint count);
	template MOON_API Buffer::Buffer(Float* data, Uint count);
	template MOON_API Buffer::Buffer(Int* data, Uint count);

	template MOON_API IndexBuffer::IndexBuffer(Uint* data, Uint count);
}