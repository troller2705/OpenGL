#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Constructor
OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFilePath, VertexShader);
	attach(desc.fragmentShaderFilePath, FragmentShader);
	link();
}

// Destructor
OShaderProgram::~OShaderProgram()
{
	for (ui32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programId);
}

ui32 OShaderProgram::getId()
{
	return m_programId;
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type)
{
	std::string shaderCode;
	std::ifstream shaderStream(shaderFilePath);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " not found");
		return;
	}

	ui32 shaderId = 0;
	if (type == VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	// Get Compile Errors
	i32 logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " compiled with errors:" << std::endl << &errorMessage[0]);
		return;
	}

	glAttachShader(m_programId, shaderId);
	m_attachedShaders[type] = shaderId;

	OGL3D_INFO("OShaderProgram | " << shaderFilePath << " compiled successfully");
}

void OShaderProgram::link()
{
	glLinkProgram(m_programId);

	// Get Compile Errors
	i32 logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << &errorMessage[0]);
		return;
	}
}
