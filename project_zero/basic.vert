#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec3 a_normal;

out vec4 v_color;
out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_position;

uniform mat4 u_modelViewProj;
uniform mat4 u_modelView;
uniform mat4 u_invModelView;

void main()
{
	gl_Position = u_modelViewProj * vec4(a_position, 1.0f);
	v_texCoord = a_texCoord;
	v_color = vec4(a_normal, 1.0f);
	v_normal =  mat3(u_invModelView) * a_normal;
	v_position = vec3(u_modelView * vec4(a_position, 1.0f));
}