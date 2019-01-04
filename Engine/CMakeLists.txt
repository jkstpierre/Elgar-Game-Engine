###############################
#  Elgar Game Engine          #
#  Author: Joseph St. Pierre  #
#  Year: 2018                 #
###############################

# Set Cmake version for compilation
cmake_minimum_required (VERSION 3.1)

# Specify the project
project(Elgar)

# Set C++ compiler flags
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Cmake includes
include(GNUInstallDirs)
include(FindPkgConfig)

# Specify the required packages
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(OPENAL REQUIRED openal)
PKG_SEARCH_MODULE(FREEALUT REQUIRED freealut)
PKG_SEARCH_MODULE(FREETYPE2 REQUIRED freetype2)
PKG_SEARCH_MODULE(GL REQUIRED gl)
PKG_SEARCH_MODULE(GLEW REQUIRED glew)

# Add all source files to the library
file(GLOB_RECURSE elgar_src "src/*.cpp")
add_library(Elgar STATIC ${elgar_src})

# Set the include directories
target_include_directories(Elgar PRIVATE .)
target_include_directories(Elgar PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(Elgar PRIVATE ${FREETYPE2_INCLUDE_DIRS})
target_include_directories(Elgar PRIVATE ${GLM_INCLUDE_DIRS})

# Link the libraries
target_link_libraries(Elgar ${SDL2_LIBRARIES})
target_link_libraries(Elgar ${OPENAL_LIBRARIES})
target_link_libraries(Elgar ${FREEALUT_LIBRARIES})
target_link_libraries(Elgar ${FREETYPE2_LIBRARIES})
target_link_libraries(Elgar ${GL_LIBRARIES})
target_link_libraries(Elgar ${GLEW_LIBRARIES})

# Generate documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Elgar.doxy ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doxygen
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM) 
endif(DOXYGEN_FOUND)

# Set install rule
install(
  TARGETS Elgar 
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install headers
install(
  DIRECTORY "./elgar"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.hpp"
)