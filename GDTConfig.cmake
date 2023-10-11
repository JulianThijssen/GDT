include(CMakeFindDependencyMacro)

# Add glfw as a dependency
find_dependency(glfw3)

include(${CMAKE_CURRENT_LIST_DIR}/GDTTargets.cmake)
