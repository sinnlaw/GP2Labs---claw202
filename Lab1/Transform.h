#ifndef Transform_h
#define Transform_h

#include <glm/glm.hpp>
#include "Component.h"

using glm::vec3;
using glm::mat4;

class Transform
{
public:
	Transform();
	~Transform();

	void update();

	vec3 setPosition(float x, float y, float z);
	vec3 getPosition();

	vec3 setScale(float x, float y, float z);
	vec3 getScale();

	vec3 setRotation(float x, float y, float z);
	vec3 getRotation();

	mat4 getModel();	

private:

	vec3 m_Position;
	vec3 m_Scale;
	vec3 m_Rotation;

	mat4 m_Model;

protected:

};



#endif