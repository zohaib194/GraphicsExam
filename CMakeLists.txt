
#CMAKE FOR GLFW GLEW 
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Exam" VERSION 0.1.0 LANGUAGES CXX)

#Set the output to the bin folder where cmake was executed
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Copy all shaders into include directory.
file(GLOB shaders ${PROJECT_SOURCE_DIR}/shader)
file(COPY ${shaders} DESTINATION ${CMAKE_BINARY_DIR}/include)

# Copy moveset file to build directory
#file(COPY ${PROJECT_SOURCE_DIR}/resources/moves/move.yaml DESTINATION ${PROJECT_BINARY_DIR}/resources/moves)

# Add all cpp files used in the Chess3D program
add_executable("Exam" 
	#src
	${PROJECT_SOURCE_DIR}/source/src/main.cpp 

	#imgui
	${PROJECT_SOURCE_DIR}/source/imgui/imgui.cpp
	${PROJECT_SOURCE_DIR}/source/imgui/imgui_impl_glfw_gl3.cpp
	${PROJECT_SOURCE_DIR}/source/imgui/imgui_draw.cpp

	#environment
	${PROJECT_SOURCE_DIR}/source/environment/Camera.cpp
	${PROJECT_SOURCE_DIR}/source/environment/LightSource.cpp

	#game
	${PROJECT_SOURCE_DIR}/source/game/HeightMap.cpp
	${PROJECT_SOURCE_DIR}/source/game/Glider.cpp

	#helpers
	${PROJECT_SOURCE_DIR}/source/helpers/errorHandler.cpp
	${PROJECT_SOURCE_DIR}/source/helpers/glfw_setup.cpp
	${PROJECT_SOURCE_DIR}/source/helpers/global_function.cpp
	
	#modeler
	${PROJECT_SOURCE_DIR}/source/modeler/Mesh.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/Model.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/Shader.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/ShaderManager.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/Texture.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/ShaderManager.cpp
)

# Find packages for linking
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

#MESSAGE( STATUS "OPENGL_LIBRARIES:	"	${OPENGL_LIBRARIES})
#MESSAGE( STATUS "GLEW_LIBRARIES:	"	${GLEW_LIBRARIES})
#MESSAGE( STATUS "glfw:				"	glfw)
#MESSAGE( STATUS "assimp:			"	assimp)
#MESSAGE( STATUS "SOIL:				"	${SOIL})

find_library(SOIL SOIL /usr/include/SOIL)

# Link the packages
target_link_libraries("Exam"
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLEW_LIBRARIES}
    PRIVATE glfw
    PRIVATE assimp
   	PRIVATE ${SOIL}
)