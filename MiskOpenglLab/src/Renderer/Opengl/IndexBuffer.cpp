#include "mkpch.h"
#include "Buffers.h"



namespace Misk {
	IndexBuffer::IndexBuffer()
	{
		
	}

	void IndexBuffer::GenBuffer()
	{
		glGenBuffers(1, &m_bufferId); // Generate the OpenGL buffer
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	}

	void IndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::SetData(const void* data, size_t size)
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_bufferId); // Delete the OpenGL buffer
	}
}