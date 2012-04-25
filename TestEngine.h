#ifndef TESTENGINE_H
#define TESTENGINE_H

#include "../GLUtils/GLFW/GLFWEngine.h"

class Shader;
class BasicTexture;

class TestEngine :
	public GLFWEngine
{
public:
	TestEngine(void);
	~TestEngine(void);
	void Update(TimeInfo& timeInfo);
	void Display();
	void Setup();
	void KeyPressed(int code);
	void KeyReleased(int code);
private:
	Shader* textDraw;
	BasicTexture* fontTex;
};

#endif

