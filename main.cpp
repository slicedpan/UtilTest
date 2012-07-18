#include <GL\glew.h>
#include <GL\glfw.h>
#include "../GLUtils/Colour.h"
#include "../GLUtils/ShaderManager.h"
#include "TestEngine.h"

int windowWidth = 1280;
int windowHeight = 720;

BasicEngine* engine;

class blah
{
public:
	const int& X;
	const int& Y;
	blah()
		: X(xPos),
		Y(yPos)
	{
		xPos = 2;
		yPos = 5;
	}
private:
	int xPos;
	int yPos;
	static int myInt;
	std::vector<void*> textures;
	std::vector<GLuint> renderBuffers;
};

int blah::myInt = 0;


class BlahContainer
{
public:
	void AddBlah(blah* theBlah)
	{
		blahMap.insert(std::pair<std::string, blah*>("blah", theBlah));		
	}
private:
	std::map<std::string, blah*> blahMap;
};

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

	BlahContainer bc;

	bc.AddBlah(new blah());

	engine = new TestEngine();
	engine->Run();

	glfwTerminate();

	return 0;
}