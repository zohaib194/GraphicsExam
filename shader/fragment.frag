#version 330 core
out vec4 FragColor;
out vec3 color;


in vec2 TexCoords;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in vec3 position;
uniform sampler2D texture_diffuse1;
uniform float time;

float lerp(float a, float b, float dt) {
	float color;

	color = a * (1 - dt) + b * dt;

	return color;
}

void main()
{    
	float green, red, blue;

	 if(position.y >= 0 && position.y <= 15.0f) {
		if(position.y > 12.0f && position.y <= 15.0f){

			//color = lerp(vec3(0.0f, 0.7f, 0.0f), vec3(0.0f, 0.0f, 0.7f), position.y);
			red = 0.0f;
			green = lerp(0.0f, 0.7f, sin(position.y));
			blue = lerp(0.7f, 0.0f, sin(position.y));

			color = vec3(red, green, blue);
		} else {
			color = vec3(0.0f, 0.0f, 0.7f);
		}
		//printf("Passed2\n");
	} else if(position.y > 15.0f && position.y <= 20.0f){
		if(position.y > 18.0f && position.y <= 20.0f){
			red = lerp(0.0, 0.6f, sin(position.y));
			green = lerp(0.7f, red, sin(position.y));
			blue = lerp(0.0f, 0.0f, sin(position.y));

			color = vec3(red, green, blue);

			//color = lerp(vec3(0.0f, 0.0f, 0.7f), vec3(0.0f, 0.7f, 0.0f), position.y);
		} else {
			color = vec3(0.0f, 0.7f, 0.0f);
		}
	} else if(position.y > 20.0f  && position.y <= 25.0f){
		if(position.y > 23.0f && position.y <= 25.0f){
			red = lerp(0.6f, 1.0f, sin(position.y));
			green = lerp(0.5f, 1.0f, sin(position.y));
			blue = lerp(0.2f, 1.0f, sin(position.y));

			color = vec3(red, green, blue);

		} else {
			color = vec3(0.6f, 0.5f, 0.2f);
		}
	} else {
		color = vec3(1.0f, 1.0f, 1.0f);
	}
	
	vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(color * phong, 1.0f); // vec4((texture(texture_diffuse1, TexCoords).rgb * vec3(0.0f, 1.0f, 0.0f)) * phong, 1.0);
}