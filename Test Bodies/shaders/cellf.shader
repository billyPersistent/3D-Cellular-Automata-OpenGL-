#version 330 core

layout(location = 0) out vec4 color;

in vec3 f_Color;
in float f_Visible;

void main()
{
	if (f_Visible == 0.0)
	{
		discard;
	}

	color = vec4(f_Color, 1.0);
}