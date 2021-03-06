#include "Window.h"
//window object handles glfw window creation.

Window::Window(const char* title, float _scale, int _moniter) {
	//prints error msg if scale above shortest resolution dimension.
	if (_scale > 1.0f) {
		std::cout << "window scales higher then 1.0 may be larger then current screen resolution!" << std::endl;
	}

	if (!glfwInit()) throw std::exception("glfw failed to initialise!!!");

	//creates array of moniter pointers and moniter count.
	int moniterCount;
	GLFWmonitor** moniters = glfwGetMonitors(&moniterCount);

	if (moniterCount == NULL) throw std::exception("No Moniter of display found!");

	//set open GL versions and profiles.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	if (_moniter > moniterCount) {
		std::cout << "selected moniter does not exsist, program will open in window mode." << std::endl;
		_moniter = 0;
	}
	if (0 < _moniter) {
		//creates full screen moniter with 1:1 aspect ratio.
		const GLFWvidmode* mode = glfwGetVideoMode(moniters[_moniter - 1]);
		window = glfwCreateWindow(mode->width, mode->height, title, moniters[_moniter - 1], NULL);
	}
	else {
		//creates window based on resolution of primary moniter.
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int resolution = static_cast<int>((mode->width > mode->height ? mode->height : mode->width) * _scale);
		window = glfwCreateWindow(resolution, resolution, title, NULL, NULL);
	}

	//checks window was creates succesfuly.
	if (!window)
	{
		glfwTerminate();
		throw std::exception("window could not initialise");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);//sets frame rate to moniters

	//init glew and check for any init errors.
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << glewGetErrorString(err) << std::endl;
		throw std::exception("ERROR INITIALIZING GLEW!");
	}

	//prints openGL version.
	std::cout << "openGL version: " << glGetString(GL_VERSION) << std::endl;

	//open GL some hardcoded things to make renders nicer.
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
}


Window::~Window()
{
	glfwTerminate();
}

//main run loop, will not return until termniated.
void Window::Run(Renderer* renderer)
{
	bool close = false;
	//MAIN RENDERER LOOP HERE!!!!
	while (!glfwWindowShouldClose(window))
	{
		/*RENDER HERE*/
		//uses draw fucntion from passed renderer pointer.
		renderer->Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}
}


