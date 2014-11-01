#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::update()
{
	mat4 translate = glm::translate(translate, m_Position);
}