#include "mkpch.h"
#include "Mesh.h"


#include <glad/glad.h>

namespace Misk {

	Mesh::Mesh()
	{
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		this->mVertices = vertices;
		this->mIndices = indices;
		this->m_VBO.GenBuffer();
		this->m_EBO.GenBuffer();
		MK_CORE_TRACE("the buffer Id:", (int)m_VBO.Getm_bufferId());
	}

	void Mesh::initMesh()
	{
		glGenVertexArrays(1, &this->m_VAO);


		glBindVertexArray(this->m_VAO);

		//vertex buffer object
		
		m_VBO.SetData(&mVertices[0], mVertices.size() * sizeof(Vertex));
		//glBindBuffer(GL_ARRAY_BUFFER, this->mBufferObj.VBO);
		//glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

		//element buffer object
		
		m_EBO.SetData(&mIndices[0], mIndices.size() * sizeof(unsigned int));
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferObj.EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//normal position
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
		//texture positions
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoords)));

		glBindVertexArray(0);
	}

	void Mesh::DrawMesh()
	{
		glBindVertexArray(this->m_VAO);
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
	}

}
