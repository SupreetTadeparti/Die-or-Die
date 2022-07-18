#pragma once

#include "Core.h"

namespace Moon
{
	class Buffer
	{
	public:
		template <typename T>
		MOON_API Buffer(T* data, Uint count);
		MOON_API inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); };
		MOON_API inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); };
		MOON_API inline Uint GetID() const { return m_BufferID; };
	private:
		Uint m_BufferID;
	};

	class MOON_API IndexBuffer
	{
	public:
		template <typename T>
		MOON_API IndexBuffer(T* data, Uint count);
		inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); };
		inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };
		inline Uint GetID() const { return m_BufferID; };
		inline Uint GetCount() const { return m_Count; };
	private:
		Uint m_BufferID;
		Uint m_Count;
	};

	class MOON_API VertexBuffer
	{
	public:
		VertexBuffer(int location, int size, int stride, int pointer, Buffer* buffer);

		// Getters
		inline Int GetLocation() const { return m_Location; };
		inline Int GetSize() const { return m_Size; };
		inline Int GetStride() const { return m_Stride; };
		inline Int GetPointer() const { return m_Pointer; };
		inline Buffer* GetBuffer() const { return m_Buffer; };
	private:
		Int m_Location;
		Int m_Size;
		Int m_Stride;
		Int m_Pointer;
		Buffer* m_Buffer;
	};
}