#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoo;
layout(location = 2) in vec3 normal;



out vec2 v_texCoo;

uniform mat4 u_MVP;

void main() {
	gl_Position = u_MVP * position;
	v_texCoo = texCoo;
};


#shader fragment
#version 330 core

out vec4 color;

in vec2 v_texCoo;

uniform sampler2D u_Texture;

void main() {
	vec4 texColor = texture(u_Texture, v_texCoo);
	color = texColor;
};