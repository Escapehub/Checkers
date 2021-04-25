cmake_minimum_required(VERSION 3.16)

project(Checkers VERSION 1.0.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

IF (WIN32)
	set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
ENDIF()

# Enable debug symbols by default
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug 
    CACHE STRING 
      "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set option to control setting the resource path variable
option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)


# Link sfml statically 
set(SFML_STATIC_LIBRARIES TRUE)

# Fin SFML shared libraries
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

FILE(
	GLOB
    SOURCES
    "src/*.cpp"
    "include/*.h"
)

# Compile executable
add_executable(Checkers ${SOURCES})

# Set include directory search paths
target_include_directories(Checkers 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

# Set executable RPATH
set_target_properties(Checkers
  PROPERTIES
      INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
)

# Link executable to required SFML modules
target_link_libraries(Checkers sfml-graphics sfml-audio)

# Set executable install location
install(TARGETS Checkers DESTINATION bin)

# Set install location for resources
install(DIRECTORY content
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
)
