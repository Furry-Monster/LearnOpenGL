// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
//
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
//
// #include <iostream>
// #include <windows.h>
// #include <stb/stb_image.h>
//
// #include "camera.h"
// #include "shader.h"
//
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in);
// void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
// void process_input(GLFWwindow* window);
// unsigned int load_texture(const char* path);
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
// int main()
// {
// 	// auto close console window
// 	// -------------------------
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
// 	glfwSetCursorPosCallback(window, mouse_callback);
// 	glfwSetScrollCallback(window, scroll_callback);
//
// 	// tell GLFW to capture our mouse
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
// 	const shader lighting_shader("ch12_vertex.glsl", "ch12_fragment.glsl");
// 	const shader light_cube_shader("ch9_lightpoint_vertex.glsl", "ch9_lightpoint_fragment.glsl");
//
// 	// set up vertex data (and buffer(s)) and configure vertex attributes
// 	// ------------------------------------------------------------------
// 	const float vertices[] = {
// 		// positions          // normals           // texture coords
// 		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
// 		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
// 		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
// 		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
// 		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
// 		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
// 		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
// 		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
// 		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
// 		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
// 		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
// 		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
// 		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
// 		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
// 		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
// 		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
// 		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
// 		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
// 		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
// 	};
// 	// positions all containers
// 	const glm::vec3 cube_positions[] = {
// 		glm::vec3(0.0f,  0.0f,  0.0f),
// 		glm::vec3(2.0f,  5.0f, -15.0f),
// 		glm::vec3(-1.5f, -2.2f, -2.5f),
// 		glm::vec3(-3.8f, -2.0f, -12.3f),
// 		glm::vec3(2.4f, -0.4f, -3.5f),
// 		glm::vec3(-1.7f,  3.0f, -7.5f),
// 		glm::vec3(1.3f, -2.0f, -2.5f),
// 		glm::vec3(1.5f,  2.0f, -2.5f),
// 		glm::vec3(1.5f,  0.2f, -1.5f),
// 		glm::vec3(-1.3f,  1.0f, -1.5f)
// 	};
// 	// positions all point lights
// 	const glm::vec3 point_light_positions[] = {
// 		glm::vec3(0.7f,  0.2f,  2.0f),
// 		glm::vec3(2.3f, -3.3f, -4.0f),
// 		glm::vec3(-4.0f,  2.0f, -12.0f),
// 		glm::vec3(0.0f,  0.0f, -3.0f)
// 	};
//
// 	// first, configure the cube's VAO (and VBO)
// 	unsigned int vbo, cube_vao;
// 	glGenVertexArrays(1, &cube_vao);
// 	glGenBuffers(1, &vbo);
//
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
// 	glBindVertexArray(cube_vao);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
// 	glEnableVertexAttribArray(1);
// 	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
// 	glEnableVertexAttribArray(2);
//
// 	// second, configure the light cube's VAO
// 	unsigned int light_vao;
// 	glGenVertexArrays(1, &light_vao);
//
// 	glBindVertexArray(light_vao);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
// 	glEnableVertexAttribArray(0);
//
// 	// load textures (we now use a utility function to keep the code more organized)
// 	// -----------------------------------------------------------------------------
// 	const unsigned int diffuse_map = load_texture("container2.png");
// 	const unsigned int specular_map = load_texture("container2_specular.png");
//
// 	// shader configuration
// 	// --------------------
// 	lighting_shader.use();
// 	lighting_shader.set_int("material.diffuse", 0);
// 	lighting_shader.set_int("material.specular", 1);
// 	lighting_shader.set_float("material.shininess", 32.0f);
//
// 	lighting_shader.set_vec3("dirLight.ambient", glm::vec3(0.05f));
// 	lighting_shader.set_vec3("dirLight.diffuse", glm::vec3(0.4f));
// 	lighting_shader.set_vec3("dirLight.specular", glm::vec3(0.5f));
// 	lighting_shader.set_vec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//
// 	lighting_shader.set_vec3("pointLights[0].position", point_light_positions[0]);
// 	lighting_shader.set_vec3("pointLights[0].ambient", glm::vec3(0.05f));
// 	lighting_shader.set_vec3("pointLights[0].diffuse", glm::vec3(0.4f));
// 	lighting_shader.set_vec3("pointLights[0].specular", glm::vec3(1.0f));
// 	lighting_shader.set_float("pointLights[0].constant", 1.0f);
// 	lighting_shader.set_float("pointLights[0].linear", 0.09f);
// 	lighting_shader.set_float("pointLights[0].quadratic", 0.032f);
//
// 	lighting_shader.set_vec3("pointLights[1].position", point_light_positions[1]);
// 	lighting_shader.set_vec3("pointLights[1].ambient", glm::vec3(0.05f));
// 	lighting_shader.set_vec3("pointLights[1].diffuse", glm::vec3(0.4f));
// 	lighting_shader.set_vec3("pointLights[1].specular", glm::vec3(1.0f));
// 	lighting_shader.set_float("pointLights[1].constant", 1.0f);
// 	lighting_shader.set_float("pointLights[1].linear", 0.09f);
// 	lighting_shader.set_float("pointLights[1].quadratic", 0.032f);
//
// 	lighting_shader.set_vec3("pointLights[2].position", point_light_positions[2]);
// 	lighting_shader.set_vec3("pointLights[2].ambient", glm::vec3(0.05f));
// 	lighting_shader.set_vec3("pointLights[2].diffuse", glm::vec3(0.4f));
// 	lighting_shader.set_vec3("pointLights[2].specular", glm::vec3(1.0f));
// 	lighting_shader.set_float("pointLights[2].constant", 1.0f);
// 	lighting_shader.set_float("pointLights[2].linear", 0.09f);
// 	lighting_shader.set_float("pointLights[2].quadratic", 0.032f);
//
// 	lighting_shader.set_vec3("pointLights[3].position", point_light_positions[3]);
// 	lighting_shader.set_vec3("pointLights[3].ambient", glm::vec3(0.05f));
// 	lighting_shader.set_vec3("pointLights[3].diffuse", glm::vec3(0.4f));
// 	lighting_shader.set_vec3("pointLights[3].specular", glm::vec3(1.0f));
// 	lighting_shader.set_float("pointLights[3].constant", 1.0f);
// 	lighting_shader.set_float("pointLights[3].linear", 0.09f);
// 	lighting_shader.set_float("pointLights[3].quadratic", 0.032f);
//
// 	lighting_shader.set_vec3("spotLight.ambient", glm::vec3(0.0f));
// 	lighting_shader.set_vec3("spotLight.diffuse", glm::vec3(1.0f));
// 	lighting_shader.set_vec3("spotLight.specular", glm::vec3(1.0f));
// 	lighting_shader.set_float("spotLight.constant", 1.0f);
// 	lighting_shader.set_float("spotLight.linear", 0.09f);
// 	lighting_shader.set_float("spotLight.quadratic", 0.032f);
// 	lighting_shader.set_float("spotLight.cutoff", glm::cos(glm::radians(12.5f)));
// 	lighting_shader.set_float("spotLight.outerCutoff", glm::cos(glm::radians(17.5f)));
//
//
// 	// render loop
// 	// -----------
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		// per-frame time logic
// 		// --------------------
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
// 		// be sure to activate shader when setting uniforms/drawing objects
// 		lighting_shader.use();
// 		lighting_shader.set_vec3("viewPos", camera.position);
//
// 		// light properties
// 		lighting_shader.set_vec3("spotLight.position", camera.position);
// 		lighting_shader.set_vec3("spotLight.direction", camera.front);
//
// 		// view/projection transformations
// 		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
// 		glm::mat4 view = camera.get_view_matrix();
// 		lighting_shader.set_mat4("projection", projection);
// 		lighting_shader.set_mat4("view", view);
//
// 		// bind diffuse map
// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, diffuse_map);
//
// 		// bind specular map
// 		glActiveTexture(GL_TEXTURE1);
// 		glBindTexture(GL_TEXTURE_2D, specular_map);
//
// 		// render the cube
// 		glBindVertexArray(cube_vao);
// 		for (unsigned int i = 0; i < 10; i++)
// 		{
// 			// calculate the model matrix for each object and pass it to shader before drawing
// 			auto model = glm::mat4(1.0f);
// 			model = translate(model, cube_positions[i]);
// 			const float angle = 20.0f * i;
// 			model = rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
// 			lighting_shader.set_mat4("model", model);
//
// 			glDrawArrays(GL_TRIANGLES, 0, 36);
// 		}
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
//
// 		// also draw the lamp object(s)
// 		light_cube_shader.use();
// 		light_cube_shader.set_mat4("projection", projection);
// 		light_cube_shader.set_mat4("view", view);
//
// 		// we now draw as many light bulbs as we have point lights.
// 		glBindVertexArray(light_vao);
// 		for (auto point_light_position : point_light_positions)
// 		{
// 			auto model = glm::mat4(1.0f);
// 			model = translate(model, point_light_position);
// 			model = scale(model, glm::vec3(0.1f));
// 			light_cube_shader.set_mat4("model", model);
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
// 	glDeleteTextures(1, &diffuse_map);
// 	glDeleteTextures(1, &specular_map);
// 	glDeleteVertexArrays(1, &cube_vao);
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
//
// 	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 		camera.process_keyboard(FORWARD, delta_time);
// 	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 		camera.process_keyboard(BACKWARD, delta_time);
// 	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 		camera.process_keyboard(LEFT, delta_time);
// 	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 		camera.process_keyboard(RIGHT, delta_time);
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
//
// // glfw: whenever the mouse moves, this callback is called
// // -------------------------------------------------------
// void mouse_callback(GLFWwindow* window, const double xpos_in, const double ypos_in)
// {
// 	const float xpos = static_cast<float>(xpos_in);
// 	const float ypos = static_cast<float>(ypos_in);
//
// 	if (first_mouse)
// 	{
// 		last_x = xpos;
// 		last_y = ypos;
// 		first_mouse = false;
// 	}
//
// 	const float x_offset = xpos - last_x;
// 	const float y_offset = last_y - ypos; // reversed since y-coordinates go from bottom to top
//
// 	last_x = xpos;
// 	last_y = ypos;
//
// 	camera.process_mouse_input(x_offset, y_offset);
// }
//
// // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// // ----------------------------------------------------------------------
// void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
// {
// 	camera.process_mouse_scroll(static_cast<float>(y_offset));
// }
//
// // utility function for loading a 2D texture from file
// // ---------------------------------------------------
// unsigned int load_texture(char const* path)
// {
// 	unsigned int texture_id;
// 	glGenTextures(1, &texture_id);
//
// 	int width, height, nr_components;
// 	if (unsigned char* data = stbi_load(path, &width, &height, &nr_components, 0))
// 	{
// 		GLenum format = 0;
// 		if (nr_components == 1)
// 			format = GL_RED;
// 		else if (nr_components == 3)
// 			format = GL_RGB;
// 		else if (nr_components == 4)
// 			format = GL_RGBA;
//
// 		glBindTexture(GL_TEXTURE_2D, texture_id);
// 		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
// 		glGenerateMipmap(GL_TEXTURE_2D);
//
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
// 		stbi_image_free(data);
// 	}
// 	else
// 	{
// 		std::cout << "Texture failed to load at path: " << path << '\n';
// 		stbi_image_free(data);
// 	}
//
// 	return texture_id;
// }