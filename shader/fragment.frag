#version 330 core
out vec4 FragColor;
out vec3 color;


in vec2 TexCoords;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in vec3 position;
uniform sampler2D texture_diffuse1;
//uniform vec3 color;

void main()
{    
	 if(position.y <= 15.0f) {
		
		color = vec3(0.0f, 0.0f, 0.7f);
		//printf("Passed2\n");

	} else if(position.y > 15.0f && position.y <= 20.0f){
		color = vec3(0.0f, 0.7f, 0.0f);

	} else if(position.y > 20.0f  && position.y <= 25.0f){
		color = vec3(0.6f, 0.5f, 0.2f);
		//printf("Passed3\n");

	} else {
		color = vec3(1.0f, 1.0f, 1.0f);
	}

	vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(color , 1.0f); // vec4((texture(texture_diffuse1, TexCoords).rgb * vec3(0.0f, 1.0f, 0.0f)) * phong, 1.0);
}