# Specifies the CMake version we require
cmake_minimum_required (VERSION 3.9)

option(GDT_NAMESPACE "Encapsulates all classes in GDT namespace" OFF)

if(GDT_NAMESPACE)
  add_definitions(-DGDT_NAMESPACE)
endif()

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output)

# Store the name of our project in a variable called PROJECT
set(PROJECT "GDT")

# Sets the name of the project for our build
project (${PROJECT} LANGUAGES C CXX)

# Set C++11 as the language standard
set (CMAKE_CXX_STANDARD 11)

# Set our Includes folder as the place to look for library includes
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/Includes/)

# Add source subdirectory which contains the source files
add_subdirectory(Source)

# Specify the name of the project executable and which sources should be used in the project
add_library(${PROJECT} STATIC
    ${BASE}
)

set_target_properties(${PROJECT} PROPERTIES PUBLIC_HEADER "${LIBRARY_PUBLIC_HEADERS}")

# Specify the libraries to use when linking the executable
target_link_libraries (${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Libraries/glfw3.lib)

install(TARGETS ${PROJECT}
        CONFIGURATIONS Debug
        ARCHIVE DESTINATION ${OUTPUT_DIR}/lib/Debug
        PUBLIC_HEADER DESTINATION ${OUTPUT_DIR}/include
)
install(TARGETS ${PROJECT}
        CONFIGURATIONS Release
        ARCHIVE DESTINATION ${OUTPUT_DIR}/lib/Release
        PUBLIC_HEADER DESTINATION ${OUTPUT_DIR}/include
)
