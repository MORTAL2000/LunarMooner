project(lunarmooner)
cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
SET(LM_STATIC_SFML FALSE CACHE BOOL "Choose whether SFML is linked statically or not.")
SET(LM_STATIC_RUNTIME FALSE CACHE BOOL "Use statically linked standard/runtime libraries? This option must match the one used for SFML.")
#SET(LM_STATIC_XY FALSE CACHE BOOL "Use statically linked xygine library?")
#TODO option to statically link xygine

if(CMAKE_COMPILER_IS_GNUCXX)
  if(LM_STATIC_RUNTIME)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -static")
  else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
  endif()
endif()

SET (CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG_")
SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

if(LM_STATIC_SFML)
  SET(SFML_STATIC_LIBRARIES TRUE)
endif()

if(WIN32)
  find_package(SFML 2 REQUIRED graphics window audio system network main)
else()
  find_package(SFML 2 REQUIRED graphics window audio system network)
endif()

if(UNIX)
  find_package(X11 REQUIRED)
endif()

find_package(XYGINE REQUIRED)

include_directories(
  ${XY_INCLUDE_DIR}
  ${SFML_INCLUDE_DIR} 
  ${CMAKE_SOURCE_DIR}/include)

if(X11_FOUND)
  include_directories(${X11_INCLUDE_DIRS})
endif()


SET(LM_DIR ${CMAKE_SOURCE_DIR}/src)
include(${LM_DIR}/CMakeLists.txt)

if(WIN32)
  add_executable(lunarmooner WIN32 ${LM_SRC})
else()
  add_executable(lunarmooner ${LM_SRC})
endif()

target_link_libraries(lunarmooner
  ${SFML_LIBRARIES}
  ${SFML_DEPENDENCIES}
  ${XY_LIBRARIES})

if(UNIX)
  target_link_libraries(lunarmooner
    ${X11_LIBRARIES})
endif()

#install executable
install(TARGETS lunarmooner
  RUNTIME DESTINATION .)

#install game data
install(DIRECTORY assets
  DESTINATION .)

#install the OpenAL DLL
if(WIN32)
  install(FILES ${SFML_INCLUDE_DIR}/../bin/openal32.dll
    DESTINATION .)
endif()
