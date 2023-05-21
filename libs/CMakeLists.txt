#GLFW 3.3
add_subdirectory(glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#GLAD
add_subdirectory(glad)
#stb
target_include_directories(glad INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}") # Not sure how to include dir for a target wise build so be it
