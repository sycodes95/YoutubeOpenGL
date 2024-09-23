#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"stb_image.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

using namespace std;

//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
//"}\n\0";

int main() 
{	// Init GLFW
	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower left corner
	//	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,// Lower right corner
	//	-0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f,// Upper corner
	//	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,// Inner left
	//	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,// Inner right
	//	0.0f / 2, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,// Inner down
	//};

	//GLuint indices[] =
	//{
	//	0, 3, 5, // Lower left triangle
	//	3, 2, 4, // Lower right triangle
	//	5, 4, 1 // Upper triangle
	//};


	// square
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

	glfwInit();


	//Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using the CORE profile
	//So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 x 800 px
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL) 
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1; 
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	// Load glad so it configues opengl
	gladLoadGL();

	// Specify the viewport of opengl in window

	// x = 0, y = 0, to x = 800, y = 800
	//glViewport(0, 0, 800, 800);
	glViewport(0, 0, 800, 800);


	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// main while loop
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// take care of all glfw events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}