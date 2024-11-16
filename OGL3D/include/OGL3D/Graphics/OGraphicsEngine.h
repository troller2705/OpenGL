#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>

class OGraphicsEngine
{
	public:
		OGraphicsEngine();
		~OGraphicsEngine();
	public:
		OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferData& data);
		OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc);
	public:
		void clear(const OVec4& color);
		void setViewport(const ORect& size);
		void setVertexArrayObject(const OVertexArrayObjectPtr& vao);
		void setShaderProgram(const OShaderProgramPtr& program);
		void drawTriangles(ui32 vertexCount, ui32 offset);
};

