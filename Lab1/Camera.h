#ifndef Camera_h
#define Camera_h

#include "Component.h"

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

class Camera:public Component
{

public:

	Camera();
	~Camera();

	void update();

	void setLook(float x, float y, float z);

	void setUp(float x, float y, float z);

	void setNearClip(float near);
	void setFarClip(float far);
	void setFOV(float FOV);

	void setAspectRatio(float ratio);

	mat4& getView();
	mat4& getProjection();

private:

	vec3 m_Position;
	vec3 m_LookAt;
	vec3 m_Up;
	float m_FOV;
	float m_AspectRatio;
	float m_NearClip;
	float m_FarClip;
	mat4 m_ViewMatrix;
	mat4 m_ProjectionMatrix;

protected:



};



#endif