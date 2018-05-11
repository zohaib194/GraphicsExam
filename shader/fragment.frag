#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
uniform sampler2D texture_diffuse1;
uniform vec4 color;

void main()
{    
	vec3 phong = ambient + diffuse + specular;
    FragColor = color; // vec4((texture(texture_diffuse1, TexCoords).rgb * vec3(0.0f, 1.0f, 0.0f)) * phong, 1.0);
}