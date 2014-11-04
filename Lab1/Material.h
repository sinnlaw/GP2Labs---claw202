#ifndef Marterial_h
#define Marterial_h

#include "Component.h"
#include <GL\glew.h>
#include <string>

class Material :public Component
{
public:

	Material();
	~Material();

	void destory();

	bool loadShader(const std::string vertexFileName, const std::string fragmentFileName);

	void bind();

	GLint getUniformLocation(const std::string& name);

private:

	GLuint m_ShaderProgram;

protected:


};

#endif