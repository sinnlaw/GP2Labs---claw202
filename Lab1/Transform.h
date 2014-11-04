#ifndef Transform_h
#define Transform_h

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

class Transform:public Component
{
public:
	Transform();
	~Transform();

	void update();

	void setPosition(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);

	vec3& getPosition();
	vec3& getScale();
	vec3& getRotation();
	mat4& getModel();	

private:

	vec3 m_Position;
	vec3 m_Scale;
	vec3 m_Rotation;

	mat4 m_Model;

protected:

};



#endif