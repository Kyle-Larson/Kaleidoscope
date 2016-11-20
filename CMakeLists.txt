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

set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
add_subdirectory("ThirdParty/SDL2" "${CMAKE_BINARY_DIR}/SDL2")
set(THIRDPARTY_INCLUDE_DIRS ${THIRDPARTY_INCLUDE_DIRS} "ThirdParty/SDL2/include")
set(THIRDPARTY_LIBS ${THIRDPARTY_LIBS} SDL2main SDL2-static)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_executable(Kaleidoscope src/main.cpp)

include_directories(${THIRDPARTY_INCLUDE_DIRS})
target_link_libraries(Kaleidoscope ${THIRDPARTY_LIBS})

install(TARGETS Kaleidoscope RUNTIME DESTINATION ${BIN_DIR})