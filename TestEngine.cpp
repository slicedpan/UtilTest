#include "TestEngine.h"
#include "../GLUtils/Shader.h"
#include "../GLUtils/GLGUI/Primitives.h"
#include "../GLUtils/Colour.h"
#include "../GLUtils/MiscUtils.h"
#include "../GLUtils/ShaderManager.h"
#include "../GLUtils/BasicTexture.h"
#include "../GLUtils/FBOManager.h"
#include "../GLUtils/QuadDrawer.h"
#include <GL\glfw.h>

TestEngine::TestEngine(void)
	: shaders(ShaderManager::GetSingleton()),
	fbos(FBOManager::GetSingleton())
{
	currentTexture = 0;
}

TestEngine::~TestEngine(void)
{
}

void TestEngine::Update(TimeInfo& timeInfo)
{
	char buf[128];
	sprintf(buf, "FPS: %d", CurrentFPS);
	glfwSetWindowTitle(buf);

	if (KeyState[GLFW_KEY_UP])
		timeStep *= 1.01f;
	if (KeyState[GLFW_KEY_DOWN])
		timeStep *= 0.99f;
	if (KeyState[GLFW_KEY_LEFT])
		spaceStep *= 0.99f;
	if (KeyState[GLFW_KEY_RIGHT])
		spaceStep *= 1.01f;

}

void TestEngine::KeyPressed(int code)
{
	if (code == 'R')
		shaders.ReloadShaders();
	if (code == GLFW_KEY_ESC)
		Exit();
	if (code == 'L')
		LoadTexture();
	if (code == 'S')
		simulate = !simulate;
	if (code == 'T')
		Step();
	if (code >= '1' && code <= '9')
	{
		currentTexture = ('1' - code) % baseTextures.size();
		CreateFBOs();
		LoadTexture();
	}
	if (code == '[')
		--currentEq;
	if (code == ']')
		++currentEq;
	if (code == 'F')
		LimitFPS = !LimitFPS;
}

void TestEngine::KeyReleased(int code)
{
	
}

void TestEngine::Step()
{		

	next->Bind();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, current->GetTextureID(0));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, last->GetTextureID(0));

	Shader* eqShader = equationShaders[currentEq % equationShaders.size()];

	eqShader->Use();
	eqShader->Uniforms["baseTex"].SetValue(0);	
	eqShader->Uniforms["previousTex"].SetValue(1);
	eqShader->Uniforms["imageSize"].SetValue(Vec2(baseTextures[currentTexture]->Width, baseTextures[currentTexture]->Height));
	eqShader->Uniforms["spaceStep"].SetValue(spaceStep);
	eqShader->Uniforms["timeStep"].SetValue(timeStep);

	QuadDrawer::DrawQuad(Vec2(-1.0, -1.0), Vec2(1.0, 1.0));

	current->Unbind();

	++iterations;

	//PrintText(Vec2(800.0, 600.0), Vec2(0.0, 0.0), "Hello World!", Colour::White);
	
	current = next;
	next = last;
	last = current;
}

bool blah = true;

void TestEngine::Display()
{
	
	int width, height;
	glfwGetWindowSize(&width, &height);

	glClear(GL_COLOR_BUFFER_BIT);

	if (simulate)
	{
		Step();		
	}
	char buf[128];

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, current->GetTextureID(0));
	shaders["RtoRGB"]->Use();
	shaders["RtoRGB"]->Uniforms["baseTex"].SetValue(0);	

	float imgWidth = (float)current->Width / width;
	imgWidth *= 2.0f;
	float imgHeight = (float)current->Height / height;
	imgHeight *= 2.0f;

	sprintf(buf, "width: %f, height: %f", imgWidth, imgHeight);
	glfwSetWindowTitle(buf);
	
	QuadDrawer::DrawQuad(Vec2(-0.8, 1.0 - imgHeight), Vec2(-0.8 + imgWidth, 1.0));

	glBindTexture(GL_TEXTURE_2D, last->GetTextureID(0));
	QuadDrawer::DrawQuad(Vec2(-1.0, 0.8), Vec2(-0.8, 1.0));
	glBindTexture(GL_TEXTURE_2D, next->GetTextureID(0));
	QuadDrawer::DrawQuad(Vec2(-1.0, 0.6), Vec2(-0.8, 0.8));

	if (blah)
	{		
		//glGetError();	
		blah = false;
	}	
	
	PrintText(Vec2(0.0, 0.0), "blah", Colour::White);
	Vec2 screenSize(width, height);
	sprintf(buf, "Equation: %s, timeStep: %f, spaceStep: %f", equationShaders[currentEq % equationShaders.size()]->GetName(), timeStep, spaceStep);
	PrintText(screenSize, Vec2(-400, -460), buf, Colour::White);
	sprintf(buf, "Iterations: %d", iterations);
	PrintText(screenSize, Vec2(-400, -500), buf, Colour::White);
	sprintf(buf, "Left/Right arrows: change space step");
	PrintText(screenSize, Vec2(-400, -540), buf, Colour::White);
	sprintf(buf, "Up/Down arrows: change time step");
	PrintText(screenSize, Vec2(-400, -580), buf, Colour::White);
	sprintf(buf, "Number keys: cycle images");
	PrintText(screenSize, Vec2(-400, -620), buf, Colour::White);
	sprintf(buf, "[/]: change equation");
	PrintText(screenSize, Vec2(-400, -660), buf, Colour::White);
	
}

void TestEngine::LoadTexture()
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, baseTextures[currentTexture]->GetId());

	fbos["ping"]->Bind();

	shaders["CopyRGBAtoR"]->Use();
	shaders["CopyRGBAtoR"]->Uniforms["baseTex"].SetValue(0);

	QuadDrawer::DrawQuad(Vec2(-1.0, -1.0), Vec2(1.0, 1.0));

	fbos["ping"]->Unbind();

	fbos["pong"]->Bind();
	QuadDrawer::DrawQuad(Vec2(-1.0, -1.0), Vec2(1.0, 1.0));
	fbos["pong"]->Unbind();

	current = fbos["ping"];
	last = fbos["pong"];
	next = fbos["pang"];

	iterations = 0;
}

void TestEngine::CreateFBOs()
{
	if (fbos.Contains("ping"))
	{
		if (fbos["ping"]->Width == baseTextures[currentTexture]->Width && fbos["ping"]->Height == baseTextures[currentTexture]->Height)
			return;
	}		
	fbos.Clear();
	fbos.AddFBO(new FrameBufferObject(baseTextures[0]->Width, baseTextures[0]->Height, 0, 0, GL_RGBA32F, GL_TEXTURE_2D, "ping"));
	fbos["ping"]->AttachTexture("tex", GL_NEAREST, GL_NEAREST);
	fbos.AddFBO(new FrameBufferObject(baseTextures[0]->Width, baseTextures[0]->Height, 0, 0, GL_RGBA32F, GL_TEXTURE_2D, "pong"));
	fbos["pong"]->AttachTexture("tex", GL_NEAREST, GL_NEAREST);
	fbos.AddFBO(new FrameBufferObject(baseTextures[0]->Width, baseTextures[0]->Height, 0, 0, GL_RGBA32F, GL_TEXTURE_2D, "pang"));
	fbos["pang"]->AttachTexture("tex", GL_NEAREST, GL_NEAREST);
	fbos["ping"]->CheckCompleteness();
	fbos["pong"]->CheckCompleteness();
	fbos["pang"]->CheckCompleteness();

	current = fbos["ping"];
	last = fbos["pong"];
	next = fbos["pang"];
}

void TestEngine::Setup()
{

	baseTextures.push_back(new BasicTexture("Assets/Textures/landscape.jpg"));
	baseTextures.push_back(new BasicTexture("Assets/Textures/spiderpic.png"));
	baseTextures.push_back(new BasicTexture("Assets/Textures/moon.png"));	
	
	textDraw = new Shader("Assets/Shaders/textDraw.vert", "Assets/Shaders/textDraw.frag", "Print Text");
	shaders.Add(textDraw);
	shaders.Add(new Shader("Assets/Shaders/copy.vert", "Assets/Shaders/copyRGBAtoR.frag", "CopyRGBAtoR"));
	shaders.Add(new Shader("Assets/Shaders/copy.vert", "Assets/Shaders/RtoRGB.frag", "RtoRGB"));
	equationShaders.push_back(new Shader("Assets/Shaders/copy.vert", "Assets/Shaders/heatEquation.frag", "Heat Equation"));
	equationShaders.push_back(new Shader("Assets/Shaders/copy.vert", "Assets/Shaders/waveEquation.frag", "Wave Equation"));
	equationShaders.push_back(new Shader("Assets/Shaders/copy.vert", "Assets/Shaders/reverseHeat.frag", "Reverse Heat Equation"));

	for (int i = 0; i < equationShaders.size(); ++i)
	{
		shaders.Add(equationShaders[i]);
	}

	//SetTextShader(textDraw);

	ShaderManager::GetSingletonPtr()->CompileShaders();

	for (int i = 0; i < baseTextures.size(); ++i)
	{
		baseTextures[i]->Load();
	}

	currentTexture = 0;
	CreateFBOs();

	LoadTexture();

	simulate = false;

	spaceStep = 0.1;
	timeStep = 0.002;

	currentEq = 0;

}
