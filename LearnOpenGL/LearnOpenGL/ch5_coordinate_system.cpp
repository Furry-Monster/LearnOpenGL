// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include "shader.h"
//
// #include <algorithm>
// #include <iostream>
// #include <Windows.h>
// #include <stb/stb_image.h>
//
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
//
// static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// static void process_input(GLFWwindow* window);
// static void mouse_input(GLFWwindow* window, double x_pos, double y_pos);
// static void scroll_input(GLFWwindow* window, double x_offset, double y_offset);
//
// // settings
// constexpr unsigned int SCR_WIDTH = 800;
// constexpr unsigned int SCR_HEIGHT = 600;
//
// // camera props
// auto camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
// auto camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
// auto camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
// float yaw = 0.0f;
// float pitch = 0.0f;
// float fov = 55.0f;
//
// // cached
// float delta_frame = 0.0f;
// float last_frame = 0.0f;
//
// bool first_mouse = true;
// float last_x = 400.0f;
// float last_y = 300.0f;
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
// 	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
// 	if (window == nullptr)
// 	{
// 		std::cout << "Failed to create GLFW window" << '\n';
// 		glfwTerminate();
// 		return -1;
// 	}
// 	glfwMakeContextCurrent(window);
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
// 	glfwSetCursorPosCallback(window, mouse_input);
// 	glfwSetScrollCallback(window, scroll_input);
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
// 	const shader our_shader("ch5_vertex.glsl", "ch5_fragment.glsl");
//
// 	// set up vertex data (and buffer(s)) and configure vertex attributes
// 	// ------------------------------------------------------------------
// 	constexpr float vertices[] = {
// 		// location			  // texture coord
// 		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
// 		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
// 	};
// 	const glm::vec3 cube_positions[] = {
// 		  glm::vec3(0.0f,  0.0f,  0.0f),
// 		  glm::vec3(2.0f,  5.0f, -15.0f),
// 		  glm::vec3(-1.5f, -2.2f, -2.5f),
// 		  glm::vec3(-3.8f, -2.0f, -12.3f),
// 		  glm::vec3(2.4f, -0.4f, -3.5f),
// 		  glm::vec3(-1.7f,  3.0f, -7.5f),
// 		  glm::vec3(1.3f, -2.0f, -2.5f),
// 		  glm::vec3(1.5f,  2.0f, -2.5f),
// 		  glm::vec3(1.5f,  0.2f, -1.5f),
// 		  glm::vec3(-1.3f,  1.0f, -1.5f)
// 	};
//
// 	unsigned int vbo, vao, ebo;
// 	glGenVertexArrays(1, &vao);
// 	glGenBuffers(1, &vbo);
// 	glGenBuffers(1, &ebo);
//
// 	glBindVertexArray(vao);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
// 	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
// 	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
// 	// position attribute
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(0));
// 	glEnableVertexAttribArray(0);
// 	// texture coord attribute
// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
// 	glEnableVertexAttribArray(1);
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
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	// set texture filtering parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	// load image, create texture and generate mipmaps
// 	int width, height, nr_channels;
// 	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
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
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	// set texture filtering parameters
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	// load image, create texture and generate mipmaps
// 	data = stbi_load("awesomeface.png", &width, &height, &nr_channels, 0);
// 	if (data)
// 	{
// 		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
// 		glGenerateMipmap(GL_TEXTURE_2D);
// 	}
// 	else
// 	{
// 		std::cout << "Failed to load texture" << '\n';
// 	}
// 	stbi_image_free(data);
//
// 	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
// 	// -------------------------------------------------------------------------------------------
// 	glEnable(GL_DEPTH_TEST);
// 	our_shader.use();
// 	our_shader.set_int("texture1", 0);
// 	our_shader.set_int("texture2", 1);
//
//
// 	// render loop
// 	// -----------
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		// pre-calculate frame tick
// 		// --------------------
// 		const float current_frame = static_cast<float>(glfwGetTime());
// 		delta_frame = current_frame - last_frame;
// 		last_frame = current_frame;
//
// 		// input
// 		// -----
// 		process_input(window);
//
// 		// render
// 		// ------
// 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
// 		// bind textures on corresponding texture units
// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, texture1);
// 		glActiveTexture(GL_TEXTURE1);
// 		glBindTexture(GL_TEXTURE_2D, texture2);
//
// 		// activate shader
// 		our_shader.use();
//
// 		// create look_at matrix
// 		auto view_trans = glm::mat4(1.0f);
// 		view_trans = lookAt(
// 			camera_pos,
// 			camera_pos + camera_front,
// 			camera_up
// 		);
// 		our_shader.set_mat4("view", view_trans);
//
// 		// set project matrix
// 		glm::mat4 projection_trans = glm::perspective(glm::radians(fov), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
// 		our_shader.set_mat4("projection", projection_trans);
//
// 		// render container
// 		glBindVertexArray(vao);
// 		for (unsigned int i = 0; i < 10; i++)
// 		{
// 			glm::mat4 model;
// 			model = translate(model, cube_positions[i]);
// 			const float angle = 20.0f * i;
// 			model = rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
// 			our_shader.set_mat4("model", model);
//
// 			glDrawArrays(GL_TRIANGLES, 0, 36);
// 		}
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
// 	// camera movement
// 	const float camera_speed = 10.0f * delta_frame;
// 	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 		camera_pos += camera_speed * camera_front;
// 	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 		camera_pos -= camera_speed * camera_front;
// 	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 		camera_pos -= normalize(cross(camera_front, camera_up)) * camera_speed;
// 	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 		camera_pos += normalize(cross(camera_front, camera_up)) * camera_speed;
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
//
// void mouse_input(GLFWwindow* window, const double x_pos, const double y_pos)
// {
// 	if (first_mouse)
// 	{
// 		last_x = x_pos;
// 		last_y = y_pos;
// 		first_mouse = false;
// 	}
//
// 	float x_offset = x_pos - last_x;
// 	float y_offset = y_pos - last_y;
// 	last_x = x_pos;
// 	last_y = y_pos;
//
// 	constexpr float sensitivity = 0.05f;
// 	x_offset *= sensitivity;
// 	y_offset *= sensitivity;
//
// 	yaw += x_offset;
// 	pitch += y_offset;
//
// 	pitch = std::min(pitch, 90.0f);
// 	pitch = std::max(pitch, -90.0f);
//
// 	glm::vec3 front;
// 	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
// 	front.y = sin(glm::radians(pitch));
// 	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
// 	camera_front = normalize(front);
// }
//
// void scroll_input(GLFWwindow* window, [[maybe_unused]] double x_offset, const double y_offset)
// {
// 	if (fov >= 1.0f && fov <= 45.0f)
// 		fov -= y_offset;
//
// 	fov = std::max(fov, 1.0f);
// 	fov = std::min(fov, 45.0f);
// }
