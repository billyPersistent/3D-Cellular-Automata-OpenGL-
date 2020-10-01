#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in float visible;

out vec3 f_Color;
out float f_Visible;

uniform mat4 u_Rotation;
uniform mat4 u_Camera;

void main()
{
	f_Color = color;
	f_Visible = visible;

	gl_Position = u_Camera * u_Rotation * position;
}