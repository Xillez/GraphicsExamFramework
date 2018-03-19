
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
file(COPY ${shaders} DESTINATION ${PROJECT_BINARY_DIR}/include)

## Use doc folder for doxygen files
#find_package(doxygen)
#if(DOXYGEN_FOUND)
#
#	message("Setting up doxygen")
#	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
#	set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/doc)
#
#else()
#
#	message("Could not find doxygen")
#
#endif(DOXYGEN_FOUND)
