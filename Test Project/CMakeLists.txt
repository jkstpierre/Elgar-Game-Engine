###############################
#  Test Project               #
#  Author: Joseph St. Pierre  #
#  Year: 2018                 #
###############################

# Set Cmake version for compilation
cmake_minimum_required (VERSION 3.1)

# Specify the project
project(TestProject)

# Set C++ compiler flags
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Cmake includes
include(GNUInstallDirs)
include(FindPkgConfig)

# Specify the required packages
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image >= 2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf >= 2.0.0)
PKG_SEARCH_MODULE(OPENAL REQUIRED openal)
PKG_SEARCH_MODULE(FREEALUT REQUIRED freealut)
PKG_SEARCH_MODULE(GL REQUIRED gl)
PKG_SEARCH_MODULE(GLEW REQUIRED glew)

# Add all source files to the library
file(GLOB_RECURSE test_src "src/*.cpp")
add_executable(TestProject ${test_src})

# Set the include directories
target_include_directories(TestProject PRIVATE .)
target_include_directories(TestProject PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(TestProject PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(TestProject PRIVATE "../Engine/")

# Link to Elgar
target_link_libraries(TestProject ${CMAKE_SOURCE_DIR}/../Engine/libElgar.a)

# Link the libraries
target_link_libraries(TestProject ${SDL2_LIBRARIES})
target_link_libraries(TestProject ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TestProject ${SDL2TTF_LIBRARIES})
target_link_libraries(TestProject ${OPENAL_LIBRARIES})
target_link_libraries(TestProject ${FREEALUT_LIBRARIES})
target_link_libraries(TestProject ${GL_LIBRARIES})
target_link_libraries(TestProject ${GLEW_LIBRARIES})