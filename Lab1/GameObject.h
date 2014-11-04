#ifndef GameObject_h
#define GameObject_h

#include <string>
#include <vector>
#include "Component.h"

class Mesh;
class Material;
class Camera;
class Transform;

class GameObject
{

public:
	GameObject();
	~GameObject();
	void init();
	void update();
	void render();
	void destroy();
	void addComponent(Component	*component);

	const std::string& getName();
	void setName(const std::string& name);

	void setTransform(Transform *transform);
	void setMesh(Mesh *mesh);
	void setMaterial(Material*material);
	void setCamera(Camera *camera);

	Transform * getTransform();
	Mesh *getMesh();
	Material *getMaterial();
	Camera * getCamera();

private:

	std::string m_Name;
	std::vector<Component*> m_Components;

	Transform *m_Transform;
	Mesh *m_Mesh;
	Material *m_Material;
	Camera *m_Camera;

protected:



};


#endif