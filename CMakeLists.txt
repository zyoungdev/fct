#[[
    This file is part of fct.

    fct is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fct is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with fct.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2018 Zachary Young
    ]]

cmake_minimum_required( VERSION 3.10.3 )
project( fct )

SET( CMAKE_CXX_STANDARD 17 )
SET( CMAKE_CXX_STANDARD_REQUIRED ON )

set( GCC_FLAGS "-fmax-errors=1 -Wall -Weffc++ -Wextra -Werror" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ${GCC_FLAGS}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g ${GCC_FLAGS}" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 ${GCC_FLAGS}" )
set( CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_RELEASE} -Os ${GCC_FLAGS}" )

add_definitions( -DDEBUG_EXTRA )

# Use include paths relative to ./{project_dir}
INCLUDE_DIRECTORIES( "${CMAKE_SOURCE_DIR}" )

set(
    LIBRARY_FILES
    fct/internal/include.h
    fct/internal/using.h
    fct/internal/transition.h
    fct/internal/show.h
    fct/internal/print.h
    fct/prelude.h
    fct/data/maybe.h
    fct/data/list.h
    fct/data/list.split.h
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

set( CATCH_INCLUDE_DIR /usr/include/catch2 )
add_library( Catch INTERFACE )
target_include_directories( Catch INTERFACE ${CATCH_INCLUDE_DIR} )

add_library( fct STATIC ${LIBRARY_FILES} )
set_target_properties( fct PROPERTIES LINKER_LANGUAGE CXX )

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" )

add_executable( tests ${TEST_FILES} )
target_link_libraries( tests fct Catch )

add_executable( main ${MAIN_FILES} )
target_link_libraries( main fct )
