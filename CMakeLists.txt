# Specifies the CMake version we require
cmake_minimum_required (VERSION 3.9)

#--------------------------------------------------------------------
# GLOBAL FLAGS
#--------------------------------------------------------------------
# Option to put all classes in GDT namespace
option(GDT_NAMESPACE "Encapsulates all classes in GDT namespace" OFF)

if(GDT_NAMESPACE)
  add_definitions(-DGDT_NAMESPACE)
endif()

# Set C++11 as the language standard
set(CMAKE_CXX_STANDARD 11)

# Automatically install in VS
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

# Add d postfix to debug library
set(CMAKE_DEBUG_POSTFIX d)

#--------------------------------------------------------------------
# PROJECT
#--------------------------------------------------------------------
# Sets the name of the project for our build
project ("GDT" LANGUAGES C CXX VERSION 1.0.0)

# Set a default installation folder if not changed by the user
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Output CACHE PATH "Default installation directory for GDT" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Set glfw3 cmake folder
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib/cmake)
message(STATUS ${CMAKE_MODULE_PATH})
find_package(glfw3 REQUIRED)

# Add source subdirectory which contains the source files
add_subdirectory(Source)

# Specify the name of the project executable and which sources should be used in the project
add_library(${PROJECT_NAME} STATIC
    ${BASE}
)

# Set our Includes folder as the place to look for library includes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/KHR/include)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${LIBRARY_PUBLIC_HEADERS}")

# Specify the libraries to use when linking the executable
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

#--------------------------------------------------------------------
# CONFIG
#--------------------------------------------------------------------
# Write a basic config version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "GDTConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

#--------------------------------------------------------------------
# INSTALL
#--------------------------------------------------------------------
# Install artifacts to output directory
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/GDT
        RUNTIME DESTINATION bin
)

# Install config files
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION lib/cmake/GDT)
    
install(FILES "${PROJECT_NAME}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/GDT)

# Install KHR includes
install(DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty/KHR/include/KHR DESTINATION include)
