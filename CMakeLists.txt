# Specifies the CMake version we require
cmake_minimum_required (VERSION 3.1)

# Store the name of our project in a variable called PROJECT
set(PROJECT "GDT")
# Sets the name of the project for our build
project (${PROJECT})

# Set our Includes folder as the place to look for library includes
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/Includes/)

# Add source subdirectory which contains the source files
add_subdirectory(Source)

# Specify the name of the project executable and which sources should be used in the project
add_library(${PROJECT}
    ${BASE}
)

# Specify the libraries to use when linking the executable
target_link_libraries (${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Libraries/glfw3.lib)
target_link_libraries (${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Libraries/assimp.lib)
