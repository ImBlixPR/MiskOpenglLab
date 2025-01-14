#pragma once

#include <glad/glad.h>


namespace Misk {

	//class Buffer
	//{
	//	virtual void Bind() const = 0;
	//	virtual void UnBind() const = 0;
	//	virtual void Enable() const = 0;
	//};


	class VertexBuffer
	{
	public:
		VertexBuffer();

		void GenBuffer();
		void Bind() const;
		void UnBind() const;

		void SetData(const void* data, size_t size);

		inline GLuint Getm_bufferId() const { return m_bufferId; }

		~VertexBuffer();
	private:
		GLuint m_bufferId;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer();

		void GenBuffer();

		void Bind() const;
		void UnBind() const;

		void SetData(const void* data, size_t size);

		inline GLuint Getm_bufferId() const { return m_bufferId; }

		~IndexBuffer();
	private:
		GLuint m_bufferId;
	};
}