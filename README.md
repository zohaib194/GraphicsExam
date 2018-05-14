## IMT2531 – Take-Home Exam 2018 ##

# Task 1: #

Load the heightmap into a scene and color elevation ranges to resemble a somewhat 
  realistic representation of altitudinal zones.
  
	[X] You can assume that the lowest elevation level is water, and the highest are mountain tops. Correspondingly, use the colours ranging from blue (representing water), green (representing         general vegetation), brown (scarce or no vegetation), and, where applicable (see below), white to represent alpine areas.
	[]  The boundaries should not be ‘hard’, but instead show smooth transitions, while
		keeping the zones distinguishable (i.e. no linear interpolation from blue to brown
		across all zones).
	[X] To verify the boundaries, introduce contour lines the can the switched on/off 
		using the key ‘o’.

You will need to provide a free-moving camera, whose orientation is controlled by the mouse
and whose position is controlled using the keys ‘i’ and ‘k’ for z axis, ‘j’ and ‘l’ for x axis, and ‘y’ and ‘h’ for y axis. Implement zooming in or out of the scene using ‘n’ and ‘m’.

		[X] Ensure that the sensitivity is reasonable.

This scene should be used to showcase seasonal change over the year. This includes the
representation of summer, autumn, winter and spring changes over the year in a continuous
cycle. This means that the altitude zone distribution changes, with snow zone taking over in
winter, and the recovery of the zone distribution in summer time.

		[X] The season needs to be printed on the top left of the output window. If you want 
			to break it down further, you can also print associated months.
		[X] The seasonal change is automated by default, but the user should be able to pause 
			it by pressing ‘5’. Letters ‘1’ to ‘4’ allow the user to switch between ‘Spring’, ‘Summer’, ‘Autumn’ and ‘Winter’, respectively.

Independent of the seasonal cycle, you will implement a daylight cycle, that is, account for the movement of sun from dawn till dusk across the scene.

		[X] Similar to the seasonal cycle, the stages of the daytime cycle 
			should printed on the top right, with individual phases including morning, noon, afternoon, and night. If you want to refine it further, you can print the time.
		[X] The user should be able to switch between individual phases sing 
			the letters ‘6’ to ‘9’. The number ‘0’ allows the de/activation of the automated movement.

Advanced tasks:

		o  Combining daylight cycle and season to account for daylight more or less 
			accurately.
		o  Ensure smooth transitions when switching between seasons.
		[X] Account for rising water levels in spring.
		o  Smoothing surface using tessellation.
		o  Introduce shadows.
		o  Position trees on surface, corresponding to altitude level.
		o  Introduce clouds, e.g. by billboarding.

# Task 2: #

Load the glider model provided as part of the resources and position it in the scene. The
proportions of scene and model don’t need to be accurate, but should appear somewhat
realistic and playable (that is, the glider should not be too small to vanish in the scene, yet not appear disproportionally large).

		[Partially] The model’s orientation should be controllable using the WASD keys.
		[Partially]	The model should be moving towards the direction it is facing at a 
					minimum speed (i.e., the model has to glide, not just sit in a fixed position)
		[X] 		The speed of the glider is controlled using ‘,’ and ‘.’
					[X]	Provide some debug output that allows the user to see the current 
						speed.
		[X] 			With the key ‘-‘, you should be able to lock the camera behind the 
						glider model to retrace its movement from a third-person perspective.
		[X] 		The key ‘f’ should allow the user to switch between different locations of the glider in the scene.
		[X]			The key ‘r’ should be used to reset the glider position.
		[X]			The glider should show specular lighting effects depending on the light	position.
Advanced tasks:

		[] 	Introduce first-person perspective and toggling between free-moving camera, third
		   	person perspective and first person perspective.
		[] 	Account for gravity effects, e.g. sinking upon deceleration and acceleration when
			direction the glider towards the surface, to give player a ‘simulation feel’, stalling effects, etc.

## Deployment Process ##

	1. Install linux.
 	2. From repository root, run mkdir build && cd build.
 	3. Build the program: 
 		Shell
 			cmake .. && make
 	4. Run the executable:
 		./bin/Exam

## Additional libraries used in exam and changes with model##

	ImGUI gui library is used in the exam to solve the problem where rendering of debug information is required.
	I have converted the glider .blend file to .obj file because the meshes were not correctly place when loaded with .blend file.

## Developer ##

- Zohaib Butt - 473219 - zohaibb@stud.ntnu.no
