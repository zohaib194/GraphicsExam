

#CMAKE FOR GLFW GLEW 
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(SRC)
  get_filename_component(projectname ${SRC} NAME_WE)
else()
  set(projectname playground)
endif(SRC)

project(${projectname})
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )

message( "system name is: " ${CMAKE_SYSTEM} )
message( "system processor is: " ${CMAKE_SYSTEM_PROCESSOR} )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET( LINUX 1)
  SET( APPLE 0)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  SET( LINUX 0)
  SET( APPLE 1 ) 
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  SET( WINDOWS 1)
endif()

find_package(OpenGL REQUIRED)


if(APPLE OR LINUX)
find_package(GLEW REQUIRED)
endif(APPLE OR LINUX)

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "turn off build examples") 
add_subdirectory(libs/glfw)
link_directories(${PROJECT_BINARY_DIR})
link_directories(${GLFW_BINARY_DIR})

add_subdirectory(libs/SOIL)
link_directories(${PROJECT_BINARY_DIR})
link_directories(${SOIL_BINARY_DIR})



include_directories(${ASSIMP_INCLUDE_DIRS})


if(WINDOWS)
link_directories(${PROJECT_SOURCE_DIR}/libs/glew/lib/)
add_subdirectory(ASSIMP)
link_directories(${PROJECT_BINARY_DIR})
link_directories(${ASSIMP_BINARY_DIR})
endif(WINDOWS)


add_executable(${projectname}
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
#add_executable(${projectname} ${srcfile} )
if(WINDOWS)
	target_link_libraries(${projectname} glfw glew32 SOIL assimp ${GLFW_LIBRARIES}  ${SOIL_LIBRARIES} ${ASSIMP_LIBRARIES} ) 
else()
	target_link_libraries(${projectname} glfw SOIL assimp ${GLEW_LIBRARY} ${GLFW_LIBRARIES}  ${SOIL_LIBRARIES} ${ASSIMP_LIBRARIES}) 
endif(WINDOWS)



include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/libs/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/libs/soil/src/)
include_directories(${PROJECT_SOURCE_DIR}/libs/glm/)
include_directories(${PROJECT_SOURCE_DIR}/libs/glm/gtx/)
include_directories(${PROJECT_SOURCE_DIR}/libs/glm/gtc/)
include_directories(${PROJECT_SOURCE_DIR}/libs/glew/include/)
include_directories(${PROJECT_SOURCE_DIR}/libs/assimp/include/)


if(WINDOWS)
include_directories(${PROJECT_SOURCE_DIR}/libs/glew/include/)

file(COPY  ${PROJECT_SOURCE_DIR}/libs/dll/glew32.dll DESTINATION ${PROJECT_BINARY_DIR})
endif(WINDOWS)

if(APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${GLEW_INCLUDE_DIRS}")
endif(APPLE)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY LINK_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()