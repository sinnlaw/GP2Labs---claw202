#include "Shader.h"
//Load it from a memory buffer

GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType)
{
	GLuint program = glCreateShader(shaderType);
	glShaderSource(program, 1, &pMem, NULL);
	glCompileShader(program);
	
	if (checkForCompilerErrors(program))
	{
		return 0;
	}

	return program;
}

//Load Sharder from file
GLuint loadShaderFromFile(const std::string&filename, SHADER_TYPE shaderType)
{
	std::string fileContents;
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file)
	{
		return 0;
	}
	//calculate file size
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);

		if (len == 0)
		{
			std::cout<< "File has no contents" << std::endl;
			return 0;
		}

		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = loadShaderFromMemory(fileContents.c_str(), shaderType);
		return program;
	}

	return 0;

}

bool checkForCompilerErrors(GLuint shaderProgram)
{
	GLint isCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::string infoLog;
		infoLog.resize(maxLength);
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Shader not compiled " << infoLog << std::endl;

		//We don't need the shader anymore.
		glDeleteShader(shaderProgram);
		return true;

	}
	return false;
}

bool checkForLinkErrors(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::string infoLog;
		glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Shader not linked" << infoLog << std::endl;

		//We don't need the shader anymore.
		glDeleteProgram(program);
		return true;
	}

	return false;

}
