cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(MAIN LANGUAGES CXX) 

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE) 

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -w")

#find_package( PythonInterp REQUIRED)
find_package( PythonLibs REQUIRED )

 set(BOOST_ROOT C:/boost/boost)
 set(Boost_USE_STATIC_LIBS     OFF) 
 SET(Boost_USE_MULTITHREADED   ON)
 SET(Boost_USE_STATIC_RUNTIME  OFF)
 set(Boost_ARCHITECTURE        "-x64")
 find_package(Boost REQUIRED COMPONENTS python37)  

message(STATUS "	PYTHON_LIBRARIES        = ${PYTHON_LIBRARIES}")
message(STATUS "	PYTHON_EXECUTABLE       = ${PYTHON_EXECUTABLE}")
message(STATUS "	PYTHON_INCLUDE_DIRS     = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "	Boost_LIBRARIES         = ${Boost_LIBRARIES}")
message(STATUS "	BOOST_ROOT              = ${BOOST_ROOT}")
message(STATUS "	BOOST_INCLUDE_DIRS      = ${BOOST_INCLUDE_DIRS}")
message(STATUS "	BOOST_LIBRARY_DIRS      = ${BOOST_LIBRARY_DIRS}")
message(STATUS "	Boost_FOUND             = ${Boost_FOUND}")
message(STATUS "	Boost_INCLUDE_DIRS      = ${Boost_INCLUDE_DIRS}")
message(STATUS "	Boost_LIBRARY_DIRS      = ${Boost_LIBRARY_DIRS}")
message(STATUS "	Boost_VERSION           = ${Boost_VERSION}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_hypot=hypot")
message(STATUS "    C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")

python_add_module(iir1 iir1_lab.cpp 
                       types.h 
                       ../src/iir1.cpp 
                       ../src/iir1.hpp)

include_directories( ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} )

target_link_libraries( iir1 ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} )

add_custom_command(TARGET iir1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:iir1> "../iir1.pyd"
    COMMENT "Copying pyd file..."
)
