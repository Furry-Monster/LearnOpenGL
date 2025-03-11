// #include <iostream>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <windows.h>
//
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
// void process_input(GLFWwindow* window);
//
//
//
//
// const char* vertex_shader_source =
// "#version 330 core\n"
// "layout (location = 0) in vec3 aPos;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "}\0";
//
// const char* fragment_shader_source_1 =
// "#version 330 core\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
// "}\n\0";
// const char* fragment_shader_source_2 =
// "#version 330 core\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
// "}\n\0";
//
//
//
//
// int main()
// {
// 	/*--
// 	----------- OpenGL initialization ------------
// 	*/
//
// 	// Hide the console window
// 	const HWND hwnd = GetConsoleWindow();
// 	if (hwnd)
// 	{
// 		ShowWindow(hwnd, SW_HIDE);
// 	}
//
// 	// Initialize GLFW
// 	glfwInit();
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
// 	// Create GLFW window
// 	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
// 	if (window == nullptr)
// 	{
// 		std::cout << "Fail to create GLFW window" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}
// 	glfwMakeContextCurrent(window);
//
// 	// Initialize GLAD
// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
// 	{
// 		std::cout << "Fail to initialize GLAD" << std::endl;
// 		return -1;
// 	}
//
// 	// Set viewport
// 	glViewport(0, 0, 800, 600);
//
// 	// Set callback function for window resize
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//
//
//
//
//
//
// 	/*--
// 	----------- Shader Compilation ------------
// 	*/
//
// 	// Compile vertex shader
// 	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
// 	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
// 	glCompileShader(vertex_shader);
//
// 	// test if vertex shader compiled successfully
// 	int success;
// 	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		char info_log[512];
// 		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
// 		std::cout << "Error compiling vertex shader: " + std::string(info_log) << std::endl;
// 		return -1;
// 	}
//
// 	// Compile fragment shader
// 	unsigned int fragment_shader_1 = glCreateShader(GL_FRAGMENT_SHADER);
// 	unsigned int fragment_shader_2 = glCreateShader(GL_FRAGMENT_SHADER);
// 	glShaderSource(fragment_shader_1, 1, &fragment_shader_source_1, nullptr);
// 	glShaderSource(fragment_shader_2, 1, &fragment_shader_source_2, nullptr);
// 	glCompileShader(fragment_shader_1);
// 	glCompileShader(fragment_shader_2);
//
// 	// test if fragment shader compiled successfully
// 	glGetShaderiv(fragment_shader_1, GL_COMPILE_STATUS, &success);
// 	glGetShaderiv(fragment_shader_2, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		char info_log[512];
// 		glGetShaderInfoLog(fragment_shader_1, 512, nullptr, info_log);
// 		std::cout << "Error compiling fragment shader: " + std::string(info_log) << std::endl;
// 		return -1;
// 	}
//
// 	// link shaders
// 	unsigned int shader_program_1 = glCreateProgram();
// 	unsigned int shader_program_2 = glCreateProgram();
// 	glAttachShader(shader_program_1, vertex_shader);
// 	glAttachShader(shader_program_2, vertex_shader);
// 	glAttachShader(shader_program_1, fragment_shader_1);
// 	glAttachShader(shader_program_2, fragment_shader_2);
// 	glLinkProgram(shader_program_1);
// 	glLinkProgram(shader_program_2);
//
// 	// text if linking successful
// 	glGetProgramiv(shader_program_1, GL_LINK_STATUS, &success);
// 	glGetProgramiv(shader_program_2, GL_LINK_STATUS, &success);
// 	if (!success)
// 	{
// 		char info_log[512];
// 		glGetProgramInfoLog(shader_program_1, 512, nullptr, info_log);
// 		std::cout << "Error linking shaders: " + std::string(info_log) << std::endl;
// 		return -1;
// 	}
//
// 	// delete shaders
// 	glDeleteShader(vertex_shader);
// 	glDeleteShader(fragment_shader_1);
// 	glDeleteShader(fragment_shader_2);
//
//
//
//
//
//
//
// 	/*--
// 	----------- VAO and VBO initialization ------------
// 	*/
//
// 	// Define vertices
// 	float firstTriangle[] = {
// 		-0.9f, -0.5f, 0.0f,  // left 
// 		-0.0f, -0.5f, 0.0f,  // right
// 		-0.45f, 0.5f, 0.0f,  // top 
// 	};
// 	float secondTriangle[] = {
// 		0.0f, -0.5f, 0.0f,  // left
// 		0.9f, -0.5f, 0.0f,  // right
// 		0.45f, 0.5f, 0.0f   // top 
// 	};
//
// 	// Create VBO,VAO
// 	unsigned int vbos[2], vaos[2];
// 	glGenBuffers(2, vbos);
// 	glGenVertexArrays(2, vaos);
//
// 	// First triangle:
// 	// Bind VAO
// 	glBindVertexArray(vaos[0]);
// 	// Copy VBO to cached memory
// 	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
// 	// Set vertex attribute pointers
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 	glEnableVertexAttribArray(0);
//
// 	// Second triangle:
// 	// Bind VAO
// 	glBindVertexArray(vaos[1]);
// 	// Copy VBO to cached memory
// 	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
// 	// Set vertex attribute pointers
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 	glEnableVertexAttribArray(0);
//
//
//
//
//
// 	/*--
// 	----------- Render loop ------------
// 	*/
//
// 	// Draw lines instead of filled triangles (after deno)
// 	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		// process input events
// 		process_input(window);
//
// 		// render background color
// 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT);
//
// 		// activate shader program
// 		glUseProgram(shader_program_1);
// 		glBindVertexArray(vaos[0]);
// 		glDrawArrays(GL_TRIANGLES, 0, 3);
// 		glUseProgram(shader_program_2);
// 		glBindVertexArray(vaos[1]);
// 		glDrawArrays(GL_TRIANGLES, 0, 3);
// 		glBindVertexArray(0);
//
// 		// apply double buffering
// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}
//
//
//
//
//
// 	/*--
// 	----------- Clean up ------------
// 	*/
//
// 	// Clean up VBO , VAO and shader program
// 	glDeleteVertexArrays(2, vaos);
// 	glDeleteBuffers(2, vbos);
// 	glDeleteProgram(shader_program_1);
// 	glDeleteProgram(shader_program_2);
//
// 	// Terminate GLFW
// 	glfwTerminate();
//
// 	return 0;
// }
//
//
//
//
// void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
// {
// 	glViewport(0, 0, width, height);
// }
//
//
// void process_input(GLFWwindow* window)
// {
// 	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 		glfwSetWindowShouldClose(window, true);
//
// }