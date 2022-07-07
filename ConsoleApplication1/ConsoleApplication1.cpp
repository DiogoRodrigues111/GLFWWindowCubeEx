#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

#include <boost/format.hpp>
#include <iostream>

// Controls of the keyboard
void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// controls keyboard

	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
}

// Initialize windows
GLFWwindow* initWindow(const int resX, const int resY)
{
	if (!glfwInit())
	{
		std::cout << boost::format("%s \n") %"Failed to initialize GLFW.";
		return NULL;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti-aliasing

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(resX, resY, "Window Cube", NULL, NULL);

	if (window == NULL)
	{
		std::cout << boost::format("%s \n") %"Failed to open GLFW window.";
		
		glfwTerminate();

		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, controls);

	// Get info of GPU and supported OpenGL version
	std::cout << boost::format("Renderer: %s \n") %glGetString(GL_RENDERER);
	std::cout << boost::format("OpenGL version supported %s \n") %glGetString(GL_VERSION);

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	return window;
}

// Draw cube.
void drawCube()
{
	GLfloat vertices[] =
	{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		 1,  1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};

	GLfloat colors[] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	static float alpha = 2;
	//attempt to rotate cube
	//glRotatef(alpha, 0, 1, 0);

	/* We have a color array and a vertex array */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glDrawArrays(GL_QUADS, 0, 24);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	alpha += 1;
}

// Showing windows, with draw.
void display(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(0.0, 0.8, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		gluPerspective(60, (double)windowWidth / (double)windowHeight, 0.1, 100);

		glMatrixMode(GL_MODELVIEW_MATRIX);
		glTranslatef(0, 0, -5);

		drawCube();		// draw cube routine.

		// Update Screen
		glfwSwapBuffers(window);

		// Check for any input, or window movement
		glfwPollEvents();
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window = initWindow(1024, 620);

	if (NULL != window)
	{
		// NULL != window, because 'glfwWindowShouldClose' added in display routines.

		display(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}