#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float loc_offset_x;
uniform float loc_offset_y;
uniform mat4 transform;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x + loc_offset_x,-aPos.y+loc_offset_y,aPos.z, 1.0)*transform;
    ourColor = aColor;
    TexCoord = aTexCoord;
}