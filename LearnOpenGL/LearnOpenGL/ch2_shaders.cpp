// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include <iostream>
// #include <cmath>
// #include <windows.h>
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void process_input(GLFWwindow* window);
//
// // settings
// constexpr unsigned int scr_width = 800;
// constexpr unsigned int scr_height = 600;
//
// const static char* vertex_shader_source =
// "#version 330 core\n"
// "layout (location = 0) in vec3 aPos;\n"
// "layout (location = 1) in vec3 aColor;\n"
// "out vec3 ourColor;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = vec4(aPos, 1.0);\n"
// "   ourColor = aColor;\n"
// "}\0";
//
// const static char* fragment_shader_source =
// "#version 330 core\n"
// "out vec4 FragColor;\n"
// "in vec3 ourColor;\n"
// "void main()\n"
// "{\n"
// "   FragColor = vec4(ourColor, 1.0);\n"
// "}\n\0";
//
//
//
//
//
// int main()
// {
//
//
// 	// auto hide console window
// 	// ------------------------------
// 	if (const HWND console = GetConsoleWindow(); console != nullptr)
// 	{
// 		ShowWindow(console, SW_HIDE);
// 	}
//
// 	// glfw: initialize and configure
// 	// ------------------------------
// 	glfwInit();
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
// #ifdef __APPLE__
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
//
// 	// glfw window creation
// 	// --------------------
// 	GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", nullptr, nullptr);
// 	if (window == nullptr)
// 	{
// 		std::cout << "Failed to create GLFW window" << '\n';
// 		glfwTerminate();
// 		return -1;
// 	}
// 	glfwMakeContextCurrent(window);
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
// 	// glad: load all OpenGL function pointers
// 	// ---------------------------------------
// 	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
// 	{
// 		std::cout << "Failed to initialize GLAD" << '\n';
// 		return -1;
// 	}
//
//
//
//
//
//
//
// 	// build and compile our shader program
// 	// ------------------------------------
// 	// vertex shader
// 	const unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
// 	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
// 	glCompileShader(vertex_shader);
// 	// check for shader compile errors
// 	int success;
// 	char info_log[512];
// 	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
// 		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << '\n';
// 	}
// 	// fragment shader
// 	const unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
// 	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
// 	glCompileShader(fragment_shader);
// 	// check for shader compile errors
// 	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
// 		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << '\n';
// 	}
// 	// link shaders
// 	const unsigned int shader_program = glCreateProgram();
// 	glAttachShader(shader_program, vertex_shader);
// 	glAttachShader(shader_program, fragment_shader);
// 	glLinkProgram(shader_program);
// 	// check for linking errors
// 	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
// 	if (!success) {
// 		glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
// 		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << '\n';
// 	}
// 	glDeleteShader(vertex_shader);
// 	glDeleteShader(fragment_shader);
//
//
//
//
//
//
//
// 	// set up vertex data (and buffer(s)) and configure vertex attributes
// 	// ------------------------------------------------------------------
// 	constexpr float vertices[] = {
// 		// locations         // colors
// 		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
// 		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
// 		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
// 	};
//
// 	unsigned int vbo, vao;
// 	glGenVertexArrays(1, &vao);
// 	glGenBuffers(1, &vbo);
// 	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
// 	glBindVertexArray(vao);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
// 	// position attribute
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
// 	glEnableVertexAttribArray(0);
// 	// color attribute
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
// 	glEnableVertexAttribArray(1);
//
//
//
//
//
//
//
// 	// render loop
// 	// -----------
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		// input
// 		// -----
// 		process_input(window);
//
// 		// render
// 		// ------
// 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT);
//
// 		// be sure to activate the shader before any calls to glUniform
// 		glUseProgram(shader_program);
//
// 		// update shader uniform
// 		double  time_value = glfwGetTime();
// 		float green_value = static_cast<float>(sin(time_value) / 2.0 + 0.5);
// 		int vertex_color_location = glGetUniformLocation(shader_program, "ourColor");
// 		glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
//
// 		// render the triangle
// 		glDrawArrays(GL_TRIANGLES, 0, 3);
//
// 		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
// 		// -------------------------------------------------------------------------------
// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}
//
//
//
//
//
//
// 	// optional: de-allocate all resources once they've outlived their purpose:
// 	// ------------------------------------------------------------------------
// 	glDeleteVertexArrays(1, &vao);
// 	glDeleteBuffers(1, &vbo);
// 	glDeleteProgram(shader_program);
//
// 	// glfw: terminate, clearing all previously allocated GLFW resources.
// 	// ------------------------------------------------------------------
// 	glfwTerminate();
// 	return 0;
// }
//
// // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// // ---------------------------------------------------------------------------------------------------------
// void process_input(GLFWwindow* window)
// {
// 	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 		glfwSetWindowShouldClose(window, true);
// }
//
// // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
// {
// 	// make sure the viewport matches the new window dimensions; note that width and 
// 	// height will be significantly larger than specified on retina displays.
// 	glViewport(0, 0, width, height);
// }