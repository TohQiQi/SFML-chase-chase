cmake_minimum_required(VERSION 3.5)
project(WillPower VERSION 0.99 LANGUAGES C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE "Release")
endif()

# BUILD EXTERNAL LIBRARIES
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(SFML 
		#GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1 
		SOURCE_DIR  ${CMAKE_SOURCE_DIR}/ext/SFML 
    		CMAKE_ARGS 
			-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
ExternalProject_Get_Property(SFML INSTALL_DIR)
set(SFML_LIB ${INSTALL_DIR})

# ADD SOURCE FILES AND HEADERS OF EXECUTABLE
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${SFML_LIB}/include)

set(SOURCE
	${CMAKE_SOURCE_DIR}/source/main.cpp
	${CMAKE_SOURCE_DIR}/source/Game.cpp
	${CMAKE_SOURCE_DIR}/source/Game.h
	${CMAKE_SOURCE_DIR}/source/State.cpp
	${CMAKE_SOURCE_DIR}/source/State.h
	${CMAKE_SOURCE_DIR}/source/GameState.cpp
	${CMAKE_SOURCE_DIR}/source/GameState.h
	${CMAKE_SOURCE_DIR}/source/Entity.cpp
	${CMAKE_SOURCE_DIR}/source/Entity.h
	${CMAKE_SOURCE_DIR}/source/MainMenuState.cpp
	${CMAKE_SOURCE_DIR}/source/MainMenuState.h
	${CMAKE_SOURCE_DIR}/source/Button.cpp
	${CMAKE_SOURCE_DIR}/source/Button.h
	${CMAKE_SOURCE_DIR}/source/Player.cpp
	${CMAKE_SOURCE_DIR}/source/Player.h
	${CMAKE_SOURCE_DIR}/source/MovementComponent.cpp
	${CMAKE_SOURCE_DIR}/source/MovementComponent.h
	${CMAKE_SOURCE_DIR}/source/AnimationComponent.cpp
	${CMAKE_SOURCE_DIR}/source/AnimationComponent.h
	${CMAKE_SOURCE_DIR}/source/HitBoxComponent.cpp
	${CMAKE_SOURCE_DIR}/source/HitBoxComponent.h
	${CMAKE_SOURCE_DIR}/source/PauseMenu.cpp
	${CMAKE_SOURCE_DIR}/source/PauseMenu.h
)
 
# LINK EXTERNAL LIBRARIES TO EXECUTABLE
LINK_DIRECTORIES(${SFML_LIB}/lib ${TINY_XML_LIB}/lib)

# ADD EXECUTABLE
add_executable(WillPower ${SOURCE})
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT WillPower)
	set_target_properties( WillPower PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Build")
	set_target_properties( WillPower PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Build")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif(MSVC)

# ADD DEPENDISIES FOR EXECUTABLE
add_dependencies(WillPower SFML)

TARGET_LINK_LIBRARIES(WillPower 
					optimized sfml-system		debug sfml-system-d 
					optimized sfml-window		debug sfml-window-d 
					optimized sfml-graphics		debug sfml-graphics-d 
					optimized sfml-audio		debug sfml-audio-d)                

# POST BUILD SCRIPTS
set(POST_LIB_DIR "lib")
if (WIN32)
	set(POST_LIB_DIR "bin")
endif()

ADD_CUSTOM_COMMAND(TARGET WillPower POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${SFML_LIB}/${POST_LIB_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/res" "${CMAKE_CURRENT_BINARY_DIR}/res")

