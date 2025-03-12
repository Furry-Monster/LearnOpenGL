// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include "shader.h"
//
// #include <iostream>
// #include <Windows.h>
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void process_input(GLFWwindow* window);
//
// // settings
// constexpr unsigned int scr_width = 800;
// constexpr unsigned int scr_height = 600;
//
// int main()
// {
// 	// hide console window automatically 
// 	// ------------------------------
// 	if (const HWND hwnd = GetConsoleWindow())
// 	{
// 		ShowWindow(hwnd, SW_HIDE);
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
// 		std::cout << "Failed to create GLFW window" << std::endl;
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
// 		std::cout << "Failed to initialize GLAD" << std::endl;
// 		return -1;
// 	}
//
// 	// build and compile our shader program
// 	// ------------------------------------
// 	const shader our_shader("ch2_vertex.glsl", "ch2_fragment.glsl");
//
// 	// set up vertex data (and buffer(s)) and configure vertex attributes
// 	// ------------------------------------------------------------------
// 	constexpr float vertices[] = {
// 		// positions         // colors
// 		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
// 		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
// 		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
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
// 	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
// 	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
// 	// glBindVertexArray(0);
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
// 		// render the background
// 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT);
//
// 		// render the triangle
// 		our_shader.use();
// 		const float swag_value_x = 0.5f * sinf(static_cast<float>(glfwGetTime()));
// 		const float swag_value_y = 0.5f * cosf(static_cast<float>(glfwGetTime()));
// 		our_shader.set_float("loc_offset_x", swag_value_x);
// 		our_shader.set_float("loc_offset_y", swag_value_y);
// 		glBindVertexArray(vao);
// 		glDrawArrays(GL_TRIANGLES, 0, 3);
//
// 		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
// 		// -------------------------------------------------------------------------------
// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}
//
// 	// optional: de-allocate all resources once they've outlived their purpose:
// 	// ------------------------------------------------------------------------
// 	glDeleteVertexArrays(1, &vao);
// 	glDeleteBuffers(1, &vbo);
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