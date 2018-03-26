
#CMAKE FOR GLFW GLEW 
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Chess Project" VERSION 0.1.0 LANGUAGES CXX)

#Set the output to the bin folder where cmake was executed
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Copy all shaders into include directory.
file(GLOB shaders ${PROJECT_SOURCE_DIR}/shader)
file(COPY ${shaders} DESTINATION ${CMAKE_BINARY_DIR}/include)

# Copy moveset file to build directory
file(COPY ${PROJECT_SOURCE_DIR}/resources/moves/move.yaml DESTINATION ${PROJECT_BINARY_DIR}/resources/moves/move.yaml)

# Add all cpp files used in the Chess3D program
add_executable("Chess3D" 
	${PROJECT_SOURCE_DIR}/src/main.cpp 
	${PROJECT_SOURCE_DIR}/src/errorHandler.cpp
	${PROJECT_SOURCE_DIR}/src/glfw_setup.cpp
	${PROJECT_SOURCE_DIR}/src/global_function.cpp
	${PROJECT_SOURCE_DIR}/src/piece.cpp
	${PROJECT_SOURCE_DIR}/src/yaml_parser.cpp
	

	${PROJECT_SOURCE_DIR}/class/shader.cpp
	${PROJECT_SOURCE_DIR}/class/model.cpp
	${PROJECT_SOURCE_DIR}/class/Mesh.cpp
	${PROJECT_SOURCE_DIR}/class/Texture.cpp)

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
target_link_libraries("Chess3D"
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLEW_LIBRARIES}
    PRIVATE glfw
    PRIVATE assimp
   	PRIVATE ${SOIL}
)


find_package(Doxygen)
#Set up doxygen if it is installed
if(DOXYGEN_FOUND)

	message("Setting up doxygen")
	set(DOXYGEN_IN ${PROJECT_BINARY_DIR}/CMakeDoxyfile.in)
	set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)

	# Setting folders to generate documentation for
	set(DOXYGEN_INPUT "${PROJECT_SOURCE_DIR}/class ${PROJECT_SOURCE_DIR}/header ${PROJECT_SOURCE_DIR}/src")
	set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/doc)

	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

	add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT} 
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )

	#set_target_properties(doc_doxygen
	#	PROPERTIES
	#	DOXYGEN_INPUT ""
	#	DOXYGEN_OUTPUT_DIRECTORY
	#)
else()

	message("Could not find doxygen")

endif(DOXYGEN_FOUND)
