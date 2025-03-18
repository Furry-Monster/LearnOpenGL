#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum camera_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;

class camera
{
public:
	// camera Attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;
	// euler Angles
	float yaw;
	float pitch;
	// camera options
	float movement_speed;
	float mouse_sensitivity;
	float zoom;

	explicit camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);

	glm::mat4 get_view_matrix() const;
	void process_keyboard(camera_movement direction, float delta_time);
	void process_mouse_input(float x_offset, float y_offset, GLboolean constrain_pitch = true);
	void process_mouse_scroll(float y_offset);

private:
	void update_camera_vectors();
};


#endif