#include <iostream>
// include glad first
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and config
	// -------------------------------------
	glfwInit();
	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

# ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
# endif


	// glfw window creation
	// -------------------------------------
	GLFWwindow* window = glfwCreateWindow(800, 600, "3dgami", NULL, NULL);
	// error check for window creation
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	// error check for GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile shader program
	// --------------------------------
	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	// set up vertex data (and buffer(s)) and config vertex attributes
	// ---------------------------------------------------------------
	float vertices[] = {
		// positions		// colors
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then config vertex attribute(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// render loop
	// ------------------------------------------------
	// generates the next frame when generating current frame simultaniously (solves flickering)
	while (!glfwWindowShouldClose(window))
	{
		// input
		// ----------------
		processInput(window);

		// render
		// -----------------------------
		// render test (background color)
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate resources once they've been used
	// --------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all allocated GLFW resources
	// ------------------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changes (by OS or user) this callback function executes
// --------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}