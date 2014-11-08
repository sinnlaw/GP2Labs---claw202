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
	void addChild(GameObject *child);

	void setName(const std::string& name);
	void setTransform(Transform *transform);
	void setMesh(Mesh *mesh);
	void setMaterial(Material*material);
	void setCamera(Camera *camera);
	void setParent(GameObject *parent);

	const std::string& getName();
	Transform * getTransform();
	Mesh *getMesh();
	Material *getMaterial();
	Camera * getCamera();
	GameObject *getParent();
	int getChildCount();
	GameObject *getChild(int index);

private:

	std::string m_Name;
	std::vector<Component*> m_Components;

	Transform *m_Transform;
	Mesh *m_Mesh;
	Material *m_Material;
	Camera *m_Camera;

	//Lab7 - create/read FBX file
	GameObject *m_Parent;
	std::vector<GameObject*> m_Children;


protected:



};


#endif