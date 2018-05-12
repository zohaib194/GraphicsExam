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

vec3 lerp(vec3 a, vec3 b, float height) {
	vec3 point;

	point.x = a.x * (height) + b.x * (height);
	point.y = a.y * (height) + b.y * (height);
	point.z = a.z * (height) + b.z * (height);

	return point;
}

float lerp( float minval, float maxval, float curval )
{
    return ( curval - minval ) / ( maxval - minval );
} 

void main()
{    
	float green, red, blue;

	 if(position.y >= 0 && position.y <= 15.0f) {
		if(position.y > 10.0f && position.y < 14.0f){

			//color = lerp(vec3(0.0f, 0.7f, 0.0f), vec3(0.0f, 0.0f, 0.7f), position.y);
			red = 0.0f;//lerp(0.0f, 0.0f, position.y - 5);
			green = lerp(0.7f, 0.0f, (position.y - (position.y + 5.0f) / 10.0f));
			blue = lerp(0.0f, 0.7f, (position.y - (position.y + 5.0f) / 10.0f));

			color = vec3(red, green, blue);
		} else {
			color = vec3(0.0f, 0.0f, 0.7f);
		}
		//printf("Passed2\n");
	} else if(position.y > 15.0f && position.y <= 20.0f){
		if(position.y < 18.0f){
			//color = lerp(vec3(0.0f, 0.0f, 0.7f), vec3(0.0f, 0.7f, 0.0f), position.y);
		} else {
		}
			color = vec3(0.0f, 0.7f, 0.0f);
	} else if(position.y > 20.0f  && position.y <= 25.0f){
		color = vec3(0.6f, 0.5f, 0.2f);
		//printf("Passed3\n");

	} else {
		color = vec3(1.0f, 1.0f, 1.0f);
	}
	
/*
	if(position.y > 10.0f && position.y <= 18.0f){
		red = 0.0f;
		blue = position.y / 128.0f;
		green = 1.0f - blue;
		color = vec3(red, green, blue);		
	} else {
		color = vec3(0.0f, 0.0f, 0.7f);
	}
*/
	vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(color * phong, 1.0f); // vec4((texture(texture_diffuse1, TexCoords).rgb * vec3(0.0f, 1.0f, 0.0f)) * phong, 1.0);
}