#include <GL\glew.h>
#include <GL\glfw.h>
#include "../GLUtils/Colour.h"
#include "../GLUtils/ShaderManager.h"
#include "TestEngine.h"

int windowWidth = 800;
int windowHeight = 600;

BasicEngine* engine;

int main(int argc, char** argv)
{
	if (!glfwInit())
		return 1;

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);

	if (!glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW))
		return 1;

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("%s", glewGetErrorString(err));
		return 1;
	}		

	engine = new TestEngine();
	engine->Run();

	glfwTerminate();

	return 0;
}