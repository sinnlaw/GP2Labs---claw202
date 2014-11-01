#ifndef Component_h
#define Component_h

#include <string>

class Component
{

public:

	Component();

	virtual~Component();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void destroy();

	const std::string& getType();
	bool isActive();
	void toggleActive();

private:

protected:

	std::string m_Type;
	bool m_Active;

};

#endif
