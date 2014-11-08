#include "Material.h"
#include "Shader.h"

Material::Material()
{
	m_ShaderProgram = -1;
	m_Type = "Material";
}

Material::~Material()
{
}

void Material::destory()
{
	glDeleteProgram(m_ShaderProgram);
}

void Material::bind()
{

	glUseProgram(m_ShaderProgram);

}

bool Material::loadShader(const std::string vertexFileName, const std::string fragmentFileName)
{
	GLuint vertexShaderProgram = 0;
		vertexShaderProgram = loadShaderFromFile(const_cast<std::string&>(vertexFileName), VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
		fragmentShaderProgram = loadShaderFromFile(const_cast<std::string&>(fragmentFileName), FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShaderProgram);
		glAttachShader(m_ShaderProgram, fragmentShaderProgram);
		glLinkProgram(m_ShaderProgram);
		checkForLinkErrors(m_ShaderProgram);
	
	//Delete Vs and Fs programe
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexNormals");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 3, "vertexColour");

	return true;
}

GLint Material::getUniformLocation(const std::string& name)
{

	return glGetUniformLocation(m_ShaderProgram, name.c_str());

}