cmake_minimum_required(VERSION 3.10.3)
project(fct)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++1z -fmax-errors=1 -Wall -Weffc++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -std=c++1z -fmax-errors=1 -Wall -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1z -fmax-errors=1 -Wall -Weffc++")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_RELEASE} -Os -std=c++1z -fmax-errors=1 -Wall -Weffc++")

add_definitions(-DDEBUG_EXTRA)

set(
    LIBRARY_FILES
    fct.h
)
set (
    TEST_FILES
    tests.cpp
)
set (
    MAIN_FILES
    main.cpp
)

set(CATCH_INCLUDE_DIR /usr/include/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_library( fct STATIC ${LIBRARY_FILES} )
set_target_properties(fct PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" )

add_executable(fct_test ${TEST_FILES})
target_link_libraries( fct_test fct Catch )

add_executable(fct_main ${MAIN_FILES})
target_link_libraries( fct_main fct )
