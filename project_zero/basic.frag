#version 330 core

layout(location = 0) out vec4 f_color;

in vec4 v_color;
in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_position;
uniform sampler2D u_texture;

struct DirectionalLight {
	vec3 direction;

	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

uniform vec4 u_color;
uniform DirectionalLight u_directional_light;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoord);

	vec3 view = normalize(-v_position);
	vec3 normal = normalize(v_normal);

	vec3 light = normalize(-u_directional_light.direction);
	vec3 color = vec3(texColor);
	vec3 reflection = reflect(-light, normal);
	vec3 ambient = u_directional_light.ambient * color;
	vec3 diffuse = u_directional_light.diffuse * max(dot(normal, light), 0.0) * color;
	vec3 specular = u_directional_light.specular * pow(max(dot(reflection, view), 0.000001), 1.0) * color;
	
	f_color = vec4(ambient + diffuse + specular, 1.0f);
}