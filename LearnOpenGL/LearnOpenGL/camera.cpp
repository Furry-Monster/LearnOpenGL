#include "camera.h"

#include <algorithm>

camera::camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movement_speed(SPEED),
	mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
}

camera::camera(const float pos_x, const float pos_y, const float pos_z,
	const float up_x, const float up_y, const float up_z,
	float yaw, float pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movement_speed(SPEED),
	mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->position = glm::vec3(pos_x, pos_y, pos_z);
	this->world_up = glm::vec3(up_x, up_y, up_z);
	this->yaw = yaw;
	this->pitch = pitch;
}

glm::mat4 camera::get_view_matrix() const
{
	return lookAt(position, position + front, up);
}

void camera::process_keyboard(const camera_movement direction, const float delta_time)
{
	const float velocity = movement_speed * delta_time;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void camera::process_mouse_input(float x_offset, float y_offset, const GLboolean constrain_pitch)
{
	x_offset *= mouse_sensitivity;
	y_offset *= mouse_sensitivity;

	yaw += x_offset;
	pitch += y_offset;

	if (constrain_pitch)
	{
		pitch = std::min(pitch, 89.0f);
		pitch = std::max(pitch, -89.0f);
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	update_camera_vectors();
}

void camera::process_mouse_scroll(const float y_offset)
{
	zoom -= y_offset;
	zoom = std::max(zoom, 1.0f);
	zoom = std::min(zoom, 45.0f);
}

void camera::update_camera_vectors()
{
	auto front = glm::vec3(0.0f, 0.0f, 0.0f);
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = normalize(front);

	right = normalize(cross(this->front, world_up));
	up = normalize(cross(right, this->front));
}
