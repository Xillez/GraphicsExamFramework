
#CMAKE FOR GLFW GLEW 
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Chess Project" VERSION 0.1.0 LANGUAGES CXX)

#Set the output to the bin folder where cmake was executed
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Get all cpp files for linking
#file( GLOB cppFiles ${PROJECT_SOURCE_DIR}/src/*cpp)
## Link each file
#foreach(file ${cppFiles})
#
#	#NAME_WE gets the file name without directory prefix
#	get_filename_component(fileName ${file} NAME_WE)
#
#	#Links the file
#	add_executable($fileName)
#	
#endforeach(file)

# Copy all shaders into include directory.
file(GLOB shaders ${PROJECT_SOURCE_DIR}/shader)
file(COPY ${shaders} DESTINATION ${CMAKE_BINARY_DIR}/include)

# Add all cpp files used in the Chess3D program
add_executable("Chess3D" 
	${PROJECT_SOURCE_DIR}/src/main.cpp 
	${PROJECT_SOURCE_DIR}/src/glfw_setup.cpp
	${PROJECT_SOURCE_DIR}/src/errorHandler.cpp

	${PROJECT_SOURCE_DIR}/class/shader.cpp
	${PROJECT_SOURCE_DIR}/class/model.cpp
	${PROJECT_SOURCE_DIR}/class/Mesh.cpp
	${PROJECT_SOURCE_DIR}/class/Texture.cpp)

# Find packages for linking
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

MESSAGE( STATUS "OPENGL_LIBRARIES:	"	${OPENGL_LIBRARIES})
MESSAGE( STATUS "GLEW_LIBRARIES:	"	${GLEW_LIBRARIES})
MESSAGE( STATUS "glfw:				"	glfw)
MESSAGE( STATUS "assimp:			"	assimp)
MESSAGE( STATUS "SOIL:				"	${SOIL})

find_library(SOIL SOIL /usr/include/SOIL)

# Link the packages
target_link_libraries("Chess3D"
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLEW_LIBRARIES}
    PRIVATE glfw
    PRIVATE assimp
   	PRIVATE ${SOIL}
)


# Use doc folder for doxygen files
#find_package(Doxygen)
#if(DOXYGEN_FOUND)
#
#	message("Setting up doxygen")
#	set(DOXYGEN_IN ${PROJECT_BINARY_DIR}/CMakeDoxyfile.in)
#	set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)
#
#	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#
#	add_custom_target( doc_doxygen ALL
#        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#        COMMENT "Generating API documentation with Doxygen"
#        VERBATIM )
#else()
#
#	message("Could not find doxygen")
#
#endif(DOXYGEN_FOUND)