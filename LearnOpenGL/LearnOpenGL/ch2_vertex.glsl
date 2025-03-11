#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float loc_offset_x;
uniform float loc_offset_y;
out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos.x + loc_offset_x,-aPos.y+loc_offset_y,aPos.z, 1.0);
    ourColor = aColor;
}