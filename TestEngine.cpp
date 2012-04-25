#include "TestEngine.h"
#include "../GLUtils/Shader.h"
#include "../GLUtils/GLGUI/Primitives.h"
#include "../GLUtils/Colour.h"
#include "../GLUtils/MiscUtils.h"

TestEngine::TestEngine(void)
{
}

TestEngine::~TestEngine(void)
{
}

void TestEngine::Update(TimeInfo timeInfo)
{
	
}

void TestEngine::Display()
{
	PrintText(Vec2(0.0, 0.0), "Hello World!", Colour::Black);
}

void TestEngine::Setup()
{
	textDraw = new Shader("Assets/Shaders/textDraw.vert", "Assets/Shaders/textDraw.frag", "Print Text");
	if (!textDraw->Compile())
		printf("%s", textDraw->GetErrorLog());
	SetTextShader(textDraw);
}
