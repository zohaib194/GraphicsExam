#version 330 core
out vec4 FragColor;
out vec3 color;


in vec2 TexCoords;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
uniform sampler2D texture_diffuse1;


void main()
{    
	
	vec3 phong = ambient + diffuse + specular;
    FragColor = vec4((texture(texture_diffuse1, TexCoords).rgb) * phong, 1.0);
}