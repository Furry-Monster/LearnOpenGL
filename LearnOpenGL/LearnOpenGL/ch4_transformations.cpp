// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include "shader.h"
//
// #include <algorithm>
// #include <iostream>
// #include <Windows.h>
// #include <cmath>
// #include <stb/stb_image.h>
//
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void process_input(GLFWwindow* window);
//
// // settings
// constexpr unsigned int scr_width = 800;
// constexpr unsigned int scr_height = 600;
//
// static float mix_rate = 0.2f;
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
// 	// build and compile our shader program
// 	// ------------------------------------
// 	const shader our_shader("ch2_vertex.glsl", "ch2_fragment.glsl");
//
//
//
// 	// set up vertex data (and buffer(s)) and configure vertex attributes
// 	// ------------------------------------------------------------------
// 	constexpr float vertices[] = {
// 		// positions          // colors           // texture coords
// 		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
// 		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
// 		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
// 		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
// 	};
// 	const unsigned int indices[] = {
// 		0, 1, 3, // first triangle
// 		1, 2, 3  // second triangle
// 	};
// 	unsigned int vbo, vao, ebo;
// 	glGenVertexArrays(1, &vao);
// 	glGenBuffers(1, &vbo);
// 	glGenBuffers(1, &ebo);
// 	glBindVertexArray(vao);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
// 	// position attribute
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
// 	glEnableVertexAttribArray(0);
// 	// color attribute
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
// 	glEnableVertexAttribArray(1);
// 	// texture attribute
// 	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
// 	glEnableVertexAttribArray(2);
//
//
// 	// load and create a texture 
// 	// -------------------------
// 	unsigned int texture1, texture2;
// 	// texture 1
// 	// ---------
// 	glGenTextures(1, &texture1);
// 	glBindTexture(GL_TEXTURE_2D, texture1);
// 	// set the texture wrapping parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	// set texture filtering parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
// 	int width, height, nr_channels;
// 	stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.
// 	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
// 	unsigned char* data = stbi_load("container.jpg", &width, &height, &nr_channels, 0);
// 	if (data)
// 	{
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
// 		glGenerateMipmap(GL_TEXTURE_2D);
// 	}
// 	else
// 	{
// 		std::cout << "Failed to load texture" << '\n';
// 	}
// 	stbi_image_free(data);
// 	// texture 2
// 	// ---------
// 	glGenTextures(1, &texture2);
// 	glBindTexture(GL_TEXTURE_2D, texture2);
// 	// set the texture wrapping parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
// 	// set texture filtering parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	// load image, create texture and generate mipmaps
// 	data = stbi_load("awesomeface.png", &width, &height, &nr_channels, 0);
// 	if (data)
// 	{
// 		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
// 		glGenerateMipmap(GL_TEXTURE_2D);
// 	}
// 	else
// 	{
// 		std::cout << "Failed to load texture" << '\n';
// 	}
// 	stbi_image_free(data);
//
// 	// set texture to shader
// 	our_shader.use();
// 	glUniform1i(glGetUniformLocation(our_shader.id, "texture1"), 0);
// 	our_shader.set_int("texture2", 1);
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
// 		// bind textures on corresponding texture units
// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, texture1);
// 		glActiveTexture(GL_TEXTURE1);
// 		glBindTexture(GL_TEXTURE_2D, texture2);
//
// 		glm::mat4 trans;
// 		trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
// 		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//
// 		// render the triangle
// 		our_shader.use();
// 		const float swag_value_x = 0.5f * sinf(static_cast<float>(glfwGetTime()));
// 		const float swag_value_y = 0.5f * cosf(static_cast<float>(glfwGetTime()));
// 		our_shader.set_float("loc_offset_x", swag_value_x);
// 		our_shader.set_float("loc_offset_y", swag_value_y);
// 		our_shader.set_float("mix_rate", mix_rate);
// 		glUniformMatrix4fv(glGetUniformLocation(our_shader.id, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
// 		glBindVertexArray(vao);
// 		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
// 	glDeleteBuffers(1, &ebo);
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
//
// 	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
// 	{
// 		mix_rate += 0.01f; // change this value accordingly (might be too slow or too fast based on system hardware)
// 		mix_rate = std::min(mix_rate, 1.0f);
// 	}
// 	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
// 	{
// 		mix_rate -= 0.01f; // change this value accordingly (might be too slow or too fast based on system hardware)
// 		mix_rate = std::max(mix_rate, 0.0f);
// 	}
//
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