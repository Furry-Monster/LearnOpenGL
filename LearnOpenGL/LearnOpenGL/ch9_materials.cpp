// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
//
// #include <iostream>
// #include <windows.h>
//
// #include "camera.h"
// #include "shader.h"
//
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in);
// void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
// void process_input(GLFWwindow* window);
//
//
//
// // settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;
//
// // camera
// camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// float last_x = SCR_WIDTH / 2.0f;
// float last_y = SCR_HEIGHT / 2.0f;
// bool first_mouse = true;
//
// // timing
// float delta_time = 0.0f;
// float last_frame = 0.0f;
//
// // lighting
// glm::vec3 light_pos(1.2f, 1.0f, 2.0f);
//
//
//
// int main(int argc, char* argv[])
// {
// 	// hide console window automatically 
// 	// ---------------------------------
// 	if (const HWND hwnd = GetConsoleWindow())
// 	{
// 		ShowWindow(hwnd, SW_HIDE);
// 	}
//
// 	// glfw: initialize and configure
// 	// ------------------------------
// 	if (!glfwInit())
// 	{
// 		std::cout << "Fail to init glfw" << '\n';
// 		return -1;
// 	}
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
//
// 	// bind callbacks
// 	// --------------
// 	glfwMakeContextCurrent(window);
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// 	glfwSetCursorPosCallback(window, mouse_callback);
// 	glfwSetScrollCallback(window, scroll_callback);
// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
// 	// glad: load all OpenGL function pointers
// 	// ---------------------------------------
// 	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
// 	{
// 		std::cout << "Failed to initialize GLAD" << '\n';
// 		return -1;
// 	}
//
// 	// configure global opengl state
// 	// -----------------------------
// 	glEnable(GL_DEPTH_TEST);
//
// 	// build and compile our shader zprogram
// 	// ------------------------------------
// 	const shader cube_shader("ch9_vertex.glsl", "ch9_fragment.glsl");
// 	const shader light_shader("ch9_lightpoint_vertex.glsl", "ch9_lightpoint_fragment.glsl");
//
// 	// set up vertex data (and buffer(s)) and configure vertex attributes
// 	// ------------------------------------------------------------------
// 	constexpr float vertices[] = {
// 		// position			  // normal
// 		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
// 		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
// 		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
// 		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
// 		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
// 		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
// 		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
// 		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
// 		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
// 		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
// 		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
// 		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
// 		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
// 	};
//
// 	// firstly set attribution for cube
// 	unsigned int vbo, vao;
// 	glGenVertexArrays(1, &vao);
// 	glGenBuffers(1, &vbo);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
// 	glBindVertexArray(vao);
//
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
// 	glEnableVertexAttribArray(1);
//
//
// 	// secondly set attribution for light_source(we make it a cube here)
// 	unsigned int light_vao; // vbo will be the same one,because the shape is the same
// 	glGenVertexArrays(1, &light_vao);
// 	glBindVertexArray(light_vao);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
// 	// we don't need normal vector here, so only 1 pointer is needed.
// 	glEnableVertexAttribArray(0);
//
//
//
// 	// render loop
// 	// -----------
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		// pre-calculate the frame tick
// 		// ----------------------------
// 		const float current_frame = static_cast<float>(glfwGetTime());
// 		delta_time = current_frame - last_frame;
// 		last_frame = current_frame;
//
// 		// input
// 		// -----
// 		process_input(window);
//
// 		// render
// 		// ------
// 		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
// 		// activate the shader programs
// 		cube_shader.use();
// 		cube_shader.set_vec3("viewPos", camera.position);
//
// 		// set material and light in shader
// 		cube_shader.set_vec3("material.ambient", 1.0f, 0.5f, 0.31f);
// 		cube_shader.set_vec3("material.diffuse", 1.0f, 0.5f, 0.31f);
// 		cube_shader.set_vec3("material.specular", 0.5f, 0.5f, 0.5f);
// 		cube_shader.set_float("material.shininess", 32.0f);
//
// 		cube_shader.set_vec3("light.position", light_pos);
// 		cube_shader.set_vec3("light.ambient", glm::vec3(0.2f));
// 		cube_shader.set_vec3("light.diffuse", glm::vec3(0.5f));
// 		cube_shader.set_vec3("light.specular", glm::vec3(1.0f));
//
// 		// model/view/projection transforms for cube
// 		glm::mat4 projection_trans = glm::perspective(
// 			glm::radians(camera.zoom),
// 			static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT),
// 			0.1f, 100.0f
// 		);
// 		glm::mat4 view_trans = camera.get_view_matrix();
// 		glm::mat4 model_trans = glm::mat4(1.0f);
// 		cube_shader.set_mat4("projection", projection_trans);
// 		cube_shader.set_mat4("view", view_trans);
// 		cube_shader.set_mat4("model", model_trans);
//
// 		// render the cube
// 		glBindVertexArray(vao);
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// 		// model/view/projection transforms for light
// 		light_shader.use();
// 		light_shader.set_mat4("projection", projection_trans);
// 		light_shader.set_mat4("view", view_trans);
// 		model_trans = glm::mat4(1.0f);
// 		model_trans = glm::translate(model_trans, light_pos);
// 		model_trans = glm::scale(model_trans, glm::vec3(0.1f));
// 		light_shader.set_mat4("model", model_trans);
//
// 		// render the light point(should be a smaller cube)
// 		glBindVertexArray(light_vao);
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
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
// 	glDeleteVertexArrays(1, &light_vao);
// 	glDeleteBuffers(1, &vbo);
//
// 	glfwTerminate();
// 	return 0;
// }
//
//
//
// void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
// {
// 	// make sure the viewport matches the new window dimensions; note that width and 
// 	// height will be significantly larger than specified on retina displays.
// 	glViewport(0, 0, width, height);
// }
//
// // glfw: whenever the mouse moves, this callback is called
// // -------------------------------------------------------
// void mouse_callback(GLFWwindow* window, const double x_pos_in, const double y_pos_in)
// {
// 	const float x_pos = static_cast<float>(x_pos_in);
// 	const float y_pos = static_cast<float>(y_pos_in);
//
// 	if (first_mouse)
// 	{
// 		last_x = x_pos;
// 		last_y = y_pos;
// 		first_mouse = false;
// 	}
//
// 	const float x_offset = x_pos - last_x;
// 	const float y_offset = last_y - y_pos;
//
// 	last_x = x_pos;
// 	last_y = y_pos;
//
// 	camera.process_mouse_input(x_offset, y_offset, true);
// }
//
// // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// // ----------------------------------------------------------------------
// void scroll_callback(GLFWwindow* window, [[maybe_unused]] double x_offset, const double y_offset)
// {
// 	camera.process_mouse_scroll(static_cast<float>(y_offset));
// }
//
// // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// // ---------------------------------------------------------------------------------------------------------
// void process_input(GLFWwindow* window)
// {
// 	// esc for quitting
// 	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 		glfwSetWindowShouldClose(window, true);
//
// 	// wasd for camera movement
// 	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 		camera.process_keyboard(FORWARD, delta_time);
// 	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 		camera.process_keyboard(BACKWARD, delta_time);
// 	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 		camera.process_keyboard(LEFT, delta_time);
// 	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 		camera.process_keyboard(RIGHT, delta_time);
// }