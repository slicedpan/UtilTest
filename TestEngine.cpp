#include "TestEngine.h"
#include "../GLUtils/Shader.h"
#include "../GLUtils/GLGUI/Primitives.h"
#include "../GLUtils/Colour.h"
#include "../GLUtils/MiscUtils.h"
#include "../GLUtils/ShaderManager.h"
#include "../GLUtils/BasicTexture.h"
#include <GL\glfw.h>

TestEngine::TestEngine(void)
{
}

TestEngine::~TestEngine(void)
{
}

void TestEngine::Update(TimeInfo& timeInfo)
{
	char buf[128];
	sprintf(buf, "FPS: %d", CurrentFPS);
	glfwSetWindowTitle(buf);
}

void TestEngine::KeyPressed(int code)
{
	if (code == 'R')
		ShaderManager::GetSingletonPtr()->ReloadShaders();
	if (code == GLFW_KEY_ESC)
		Exit();
}

void TestEngine::KeyReleased(int code)
{
	
}

void TestEngine::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	PrintText(Vec2(800.0, 600.0), Vec2(0.0, 0.0), "Hello World!", Colour::White);
}

void TestEngine::Setup()
{
	textDraw = new Shader("Assets/Shaders/textDraw.vert", "Assets/Shaders/textDraw.frag", "Print Text");
	Shader* copy = new Shader("Assets/Shaders/copy.vert", "Assets/Shaders/copy.frag", "Copy");
	SetTextShader(textDraw);
	ShaderManager::GetSingletonPtr()->CompileShaders();
}
