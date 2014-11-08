#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

GameObject::GameObject()
{
	m_Transform = NULL;
	m_Mesh = NULL;
	m_Material = NULL;
	m_Camera = NULL;
	m_Parent = NULL;
	m_Name = "GameObject";
}

GameObject::~GameObject()
{

}

void GameObject::init()
{

	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}

	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->init();
	}

}

void GameObject::update()
{

	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->update();
	}
	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->update();
	}

}

void GameObject::render()
{

	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->render();
	}
	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->render();
	}


}

void GameObject::destroy()
{
	auto iter = m_Components.begin();
	while (iter != m_Components.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete(*iter);
			(*iter) = NULL;
			iter = m_Components.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	m_Components.clear();

	auto gameObjiter = m_Children.begin();
	while (gameObjiter != m_Children.end())
	{

		(*gameObjiter)->destroy();
		if ((*gameObjiter))
		{
			delete(*gameObjiter);
			(*gameObjiter) = NULL;
			gameObjiter = m_Children.erase(gameObjiter);
		}
		else
		{
			gameObjiter++;
		}

		m_Children.clear();

	}

}

//add
void GameObject::addComponent(Component * component)
{
	component->setParent(this);
	m_Components.push_back(component);
}

void GameObject::addChild(GameObject *child)
{
	child->setParent(this);
	m_Children.push_back(child);
}


//set
void GameObject::setName(const std::string& name)
{
	m_Name = name;
}

void GameObject::setTransform(Transform *transform)
{
	m_Transform = transform;
	addComponent(transform);
}

void GameObject::setMesh(Mesh *mesh)
{
	m_Mesh = mesh;
	addComponent(mesh);
}

void GameObject::setMaterial(Material *marterial)
{
	m_Material = marterial;
	addComponent(marterial);
}


void GameObject::setCamera(Camera *camera)
{
	m_Camera = camera;
	addComponent(camera);
}

void GameObject::setParent(GameObject *parent)
{
	m_Parent = parent;	
}

//get

const std::string&GameObject::getName()
{
	return m_Name;
}

Transform * GameObject::getTransform()
{
	return m_Transform;
}

Mesh *GameObject::getMesh()
{
	return m_Mesh;
}

Material *GameObject::getMaterial()
{
	return m_Material;
}

Camera *GameObject::getCamera()
{
	return m_Camera;
}

GameObject *GameObject::getParent()
{
	return m_Parent;
}

int GameObject::getChildCount()
{
	return m_Children.size();
}

GameObject *GameObject::getChild(int index)
{
	if (index < m_Children.size())
		return m_Children[index];
	else
		return NULL;
}
