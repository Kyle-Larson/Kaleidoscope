# if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
#   # Use `cmake . -Bbuild` to get build files.
#   # Use `cmake --build build --config Release` to build dependencies.
#   message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the SDL source code and call cmake from there")
# endif()

cmake_minimum_required(VERSION 3.0)
project(Kaleidoscope)
set(CMAKE_MOUDLE_PATH ${CMAKE_MODULE_PATH} "${Kaleidoscope_SOURCE_DIR}/cmake")
set(BIN_DIR ${Kaleidoscope_SOURCE_DIR}/bin)

set(THIRDPARTY_INCLUDE_DIRS)
set(THIRDPARTY_LIBS)

if(NOT EMSCRIPTEN)

# GLFW Specific Vars
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(GLFW_SHARED_ENABLED_BY_DEFAULT OFF)
add_subdirectory("ThirdParty/glfw" "${CMAKE_BINARY_DIR}/glfw")
set(THIRDPARTY_INCLUDE_DIRS ${THIRDPARTY_INCLUDE_DIRS} "ThirdParty/glfw/include")
set(THIRDPARTY_LIBS ${THIRDPARTY_LIBS} glfw)

# GLEW Specific vars
set(glew-cmake_BUILD_STATIC ON CACHE BOOL "" FORCE)


add_subdirectory("ThirdParty/glew-cmake" "${CMAKE_BINARY_DIR}/glew-cmake")
set(THIRDPARTY_INCLUDE_DIRS ${THIRDPARTY_INCLUDE_DIRS} "ThirdParty/glew-cmake/include")
set(THIRDPARTY_LIBS ${THIRDPARTY_LIBS} glew)
link_directories("build/lib/Release")

# OpenGL
find_package(OpenGL REQUIRED)

set(THIRDPARTY_INCLUDE_DIRS ${THIRDPARTY_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(THIRDPARTY_LIBS ${THIRDPARTY_LIBS} ${OPENGL_LIBRARIES})

endif()

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINER_FLAGS} -s USE_GLFW=3")
endif()

add_executable(Kaleidoscope src/main.cpp)

include_directories(${THIRDPARTY_INCLUDE_DIRS})
target_link_libraries(Kaleidoscope ${THIRDPARTY_LIBS})

install(TARGETS Kaleidoscope RUNTIME DESTINATION ${BIN_DIR})