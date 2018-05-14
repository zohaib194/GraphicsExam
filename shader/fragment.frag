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
uniform int seasonMode;
uniform int time;

vec3 WHITE = vec3(1.0f, 1.0f, 1.0f);
vec3 BROWN = vec3(0.6f, 0.5f, 0.2f);
vec3 BLUE = vec3(0.0f, 0.0f, 0.7f);
vec3 GREEN = vec3(0.0f, 0.7f, 0.0f);
vec3 PINK = vec3(0.8f, 0.5f, 0.5f);

void main()
{    
	// Water level in all seasons.
	if(season == 90 && position.y <= 35.0f){										// Summer
		color = BLUE;
		// Contour Lines
		if(contour) {
			if(position.y > 33.0f && position.y <= 35.0f){
				color = PINK;
			}
		}
	} else if (season == 181 && position.y <= 30.0f){								// Authum
		color = BLUE;		
		if(contour) {
			if(position.y > 28.0f && position.y <= 30.0f){
				color = PINK;
			}
		}
	} else if (season == 272 && position.y <= 25.0f){								// Winter
		color = BLUE;			
		if(contour){
			if(position.y > 23.0f && position.y <= 25.0f){
				color = PINK;
			}
		}
	} else if (season == 363 && position.y <= 30.0f){								// Spring
		color = BLUE;
		if(contour){
			if(position.y > 28.0f && position.y <= 30.0f){
				color = PINK;
			}
		}
	}

	// Vagetation level in all seasons.
	if(season == 90 && (position.y > 35.0f && position.y <= 60.0f)){				// Summer
		color = GREEN;
		if(contour){
			if(position.y > 58.0f && position.y <= 60.0f){
				color = PINK;
			}
		}
	} else if (season == 181 && (position.y > 30.0f && position.y <= 40.0f)){		// Authum
		color = GREEN;
		if(contour){
			if(position.y > 38.0f && position.y <= 40.0f){
				color = PINK;
			}
		}
	} else if (season == 272 && (position.y > 25.0f && position.y <= 30.0f)){		// Winter
		color = WHITE;
		if(contour){
			if(position.y > 28.0f && position.y <= 30.0f){
				color = PINK;
			}
		}
	} else if (season == 363 && (position.y > 30.0f && position.y <= 50.0f)){		// Spring
		color = GREEN;
		if(contour){
			if(position.y > 48.0f && position.y <= 50.0f){
				color = PINK;
			}
		}
	}
	
	// No vagetation level in all seasons.
	if(season == 90 && (position.y > 60.0f)){										// Summer
		color = BROWN;
		if(contour){
			if(position.y > 58.0f && position.y <= 60.0f){
				color = PINK;
			}
		}
	} else if (season == 181 && (position.y > 40.0f && position.y <= 70.0f)){		// Authum
		color = BROWN;
		if(contour){
			if(position.y > 68.0f && position.y <= 70.0f){
				color = PINK;
			}
		}
	} else if (season == 272 && (position.y > 30.0f && position.y <= 40.0f)){		// Winter
		color = WHITE;
		if(contour){
			if(position.y > 38.0f && position.y <= 40.0f){
				color = PINK;
			}
		}
	} else if (season == 363 && (position.y > 50.0f && position.y <= 60.0f)){		// Spring
		color = BROWN;
		if(contour){
			if(position.y > 58.0f && position.y <= 60.0f){
				color = PINK;
			}
		}
	}
	
	// Alpine level in all seasons.
	if(season == 90 && (position.y > 70.0f)){										// Summer
		color = BROWN;
		if(contour){
			if(position.y > 68.0f && position.y <= 70.0f){
				color = PINK;
			}
		}
	} else if (season == 181 && (position.y > 70.0f)){								// Authum
		color = WHITE;
		if(contour){
			if(position.y > 68.0f && position.y <= 70.0f){
				color = PINK;
			}
		}
	} else if (season == 272 && (position.y > 25.0f)){								// Winter
		color =WHITE;
		if(contour){
			if(position.y > 23.0f && position.y <= 25.0f){
				color = PINK;
			}
		}
	} else if (season == 363 && (position.y > 60.0f)){								// Spring
		color = WHITE;
		if(contour){
			if(position.y > 58.0f && position.y <= 60.0f){
				color = PINK;
			}
		}
	}

	// Phong lighting
	vec3 phong = ambient + diffuse + specular * time;

    FragColor = vec4(color * phong, 1.0f);
}