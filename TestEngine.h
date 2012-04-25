#ifndef TESTENGINE_H
#define TESTENGINE_H

#include "../GLUtils/GLFW/GLFWEngine.h"

class Shader;

class TestEngine :
	public GLFWEngine
{
public:
	TestEngine(void);
	~TestEngine(void);
	void Update(TimeInfo timeInfo);
	void Display();
	void Setup();
private:
	Shader* textDraw;
	bool keyState[256];
};

#endif

