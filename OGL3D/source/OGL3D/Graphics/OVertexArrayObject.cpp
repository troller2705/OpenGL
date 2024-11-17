#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

// Constructor
OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& data)
{
	if (!data.listSize) OGL3D_ERROR("OVertexArrayObject | listSize in NULL");
	if (!data.vertexSize) OGL3D_ERROR("OVertexArrayObject | vertexSize in NULL");
	if (!data.verticesList) OGL3D_ERROR("OVertexArrayObject | verticesList in NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	for (ui32 i = 0; i < data.attributesListSize; i++)
	{
		glVertexAttribPointer(
			i,
			data.attributesList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			data.vertexSize,
			(void*)((i==0) ? 0 : data.attributesList[i - 1].numElements * sizeof(f32))
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

// Destructor
OVertexArrayObject::~OVertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

ui32 OVertexArrayObject::getId()
{
	return m_vertexArrayObjectId;
}

ui32 OVertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

ui32 OVertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.vertexSize;
}
