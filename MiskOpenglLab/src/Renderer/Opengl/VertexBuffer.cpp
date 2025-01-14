#include "mkpch.h"
#include "Buffers.h"


namespace Misk {


	VertexBuffer::VertexBuffer()
	{
		
	}

	void VertexBuffer::GenBuffer()
	{
		glGenBuffers(1, &m_bufferId); // Generate the OpenGL buffer
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); // Bind the buffer
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer
	}

	void VertexBuffer::SetData(const void* data, size_t size)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_bufferId); // Delete the OpenGL buffer
	}

}