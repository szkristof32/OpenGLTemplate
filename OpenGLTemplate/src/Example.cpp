#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#define WIDTH 1600
#define HEIGHT 900
#define TITLE "OpenGL Example"

int main(int argc, char** argv)
{
	glfwInit();

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
	glfwSetWindowPos(window, (vidMode->width - WIDTH) / 2, (vidMode->height - HEIGHT) / 2);

	glfwMakeContextCurrent(window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == 0)
	{
		std::cerr << "Failed to initialise glad.\n";
		return 1;
	}
	std::cout << "OpenGL Info:\n";
	std::cout << "  Vendor: " << (const char*)glGetString(GL_VENDOR) << "\n";
	std::cout << "  Renderer: " << (const char*)glGetString(GL_RENDERER) << "\n";
	std::cout << "  Version: " << (const char*)glGetString(GL_VERSION) << "\n";

	glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwShowWindow(window);
	glfwSwapInterval(1);

	float vertexData[] = {
		0.0f, 0.5f,			0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,		0.0f, 0.0f, 1.0f
	};

	GLuint vao = 0, vbo = 0;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 20, nullptr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 20, (const void*)8);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const char* vertexShader = R"(
		#version 130

		in vec2 in_position;
		in vec3 in_colour;

		out vec3 pass_colour;

		void main() {
			gl_Position = vec4(in_position, 0.0, 1.0);
			pass_colour = in_colour;
		}	
	)";

	const char* fragmentShader = R"(
		#version 130

		in vec3 pass_colour;

		out vec4 out_colour;

		void main() {
			out_colour = vec4(pass_colour, 1.0);
		}	
	)";

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShader, NULL);
	glCompileShader(vertex);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShader, NULL);
	glCompileShader(fragment);

	GLuint shader = glCreateProgram();
	glAttachShader(shader, vertex);
	glAttachShader(shader, fragment);
	glLinkProgram(shader);
	glBindAttribLocation(shader, 0, "in_position");
	glBindAttribLocation(shader, 1, "in_colour");

	glDetachShader(shader, vertex);
	glDetachShader(shader, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shader);

	glfwDestroyWindow(window);
	glfwTerminate();
}