#ifndef GameObject_h
#define GameObject_h

#include <string>
#include <vector>
#include "Component.h"

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

private:

	std::string m_Name;
	std::vector<Component*> m_Components;

protected:



};


#endif