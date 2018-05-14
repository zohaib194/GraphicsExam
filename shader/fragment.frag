#version 330 core
out vec4 FragColor;
out vec3 color;


in vec2 TexCoords;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in vec3 position;
in vec3 normal;
uniform sampler2D texture_diffuse1;
uniform bool contour;
uniform int currentDay;
uniform int season;

float lerp(float a, float b, float dt) {
	float color;

	color = a * (1 - dt) + b * dt;

	return color;
}

void main()
{    
	float green, red, blue;
/*
	 if(position.y >= 0 && position.y <= 30.0f) {
		if(position.y > 27.0f && position.y <= 30.0f){
			if(!contour) {
				red = 0.0f;
				green = lerp(0.0f, 0.7f, sin(position.y));
				blue = lerp(0.7f, 0.0f, sin(position.y));

				color = vec3(red, green, blue);
			} else {
				color = vec3(0.8f, 0.5f, 0.5f);
			}
		} else {
			color = vec3(0.0f, 0.0f, 0.7f);
		}
		//printf("Passed2\n");
	} else if(position.y > 30.0f && position.y <= 45.0f){
		if(position.y > 42.0f && position.y <= 45.0f){
			if(!contour){
				red = lerp(0.0, 0.6f, sin(position.y));
				green = lerp(0.7f, red, sin(position.y));
				blue = lerp(0.0f, 0.0f, sin(position.y));

				color = vec3(red, green, blue);
			} else {
				color = vec3(0.8f, 0.5f, 0.5f);
			}

			//color = lerp(vec3(0.0f, 0.0f, 0.7f), vec3(0.0f, 0.7f, 0.0f), position.y);
		} else {
			color = vec3(0.0f, 0.7f, 0.0f);
		}
	} else if(position.y > 45.0f  && position.y <= 70.0f){
		if(position.y > 67.0f && position.y <= 70.0f){
			if(!contour){
				red = lerp(0.6f, 1.0f, sin(position.y));
				green = lerp(0.5f, 1.0f, sin(position.y));
				blue = lerp(0.2f, 1.0f, sin(position.y));

				color = vec3(red, green, blue);				
			} else {
				color = vec3(0.8f, 0.5f, 0.5f);
			}
		} else {
			color = vec3(0.6f, 0.5f, 0.2f);
		}
	} else {
		color = vec3(1.0f, 1.0f, 1.0f);
	}

*/
	// Water level in all seasons.
	if(season == 90 && position.y <= 35.0f){
		color = vec3(0.0f, 0.0f, season-currentDay/float(season));
	} else if (season == 181 && position.y <= 30.0f){
		color = vec3(0.0f, 0.0f, season-currentDay/float(season) - 0.2f);
	} else if (season == 272 && position.y <= 25.0f){
		color = vec3(0.0f, 0.0f, season-currentDay/float(season) - 0.2f);
	} else if (season == 363 && position.y <= 30.0f){
		color = vec3(0.0f, 0.0f, season-currentDay/float(season) - 0.2f);
	}

	// Vagetation level in all seasons.
	if(season == 90 && (position.y > 35.0f && position.y <= 60.0f)){				// Summer
		color = vec3(0.0f, 0.7f, 0.0f);
	} else if (season == 181 && (position.y > 30.0f && position.y <= 40.0f)){		// Authum
		color = vec3(0.0f, 0.7f, 0.0f);
	} else if (season == 272 && (position.y > 25.0f && position.y <= 30.0f)){		// Winter
		color = vec3(1.0f, 1.0f, 1.0f);
	} else if (season == 363 && (position.y > 30.0f && position.y <= 50.0f)){		// Spring
		color = vec3(0.0f, 0.7f, 0.0f);
	}
	
	// No vagetation level in all seasons.
	if(season == 90 && (position.y > 60.0f)){										// Summer
		color = vec3(0.6f, 0.5f, 0.2f);
	} else if (season == 181 && (position.y > 40.0f && position.y <= 70.0f)){		// Authum
		color = vec3(0.6f, 0.5f, 0.2f);
	} else if (season == 272 && (position.y > 30.0f && position.y <= 40.0f)){		// Winter
		color = vec3(1.0f, 1.0f, 1.0f);
	} else if (season == 363 && (position.y > 50.0f && position.y <= 60.0f)){		// Spring
		color = vec3(0.6f, 0.5f, 0.2f);
	}
	
	// Alpine level in all seasons.
	if(season == 90 && (position.y > 70.0f)){				// Summer
		color = vec3(0.6f, 0.5f, 0.2f);
	} else if (season == 181 && (position.y > 70.0f)){		// Authum
		color = vec3(1.0f, 1.0f, 1.0f);
	} else if (season == 272 && (position.y > 25.0f)){		// Winter
		color = vec3(1.0f, 1.0f, 1.0f);
	} else if (season == 363 && (position.y > 60.0f)){		// Spring
		color = vec3(1.0f, 1.0f, 1.0f);
	}

	vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(color * phong, 1.0f);
}