#pragma once
#include <memory>

class OVertexArrayObject;
class OShaderProgram;

typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;

typedef float f32;
typedef int i32;
typedef unsigned int ui32;


struct OVertexBufferData
{
	void* verticesList = nullptr;
	ui32 vertexSize = 0;
	ui32 listSize = 0;
};

struct OShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

enum OShaderType
{
	VertexShader = 0,
	FragmentShader
};