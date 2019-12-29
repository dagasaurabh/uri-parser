cmake_minimum_required(VERSION 3.2.0)

project( URI-PARSER DESCRIPTION "C based basic uri parser" LANGUAGES C)

set( P ${PROJECT_NAME})

include_directories( ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable( ${P}
	${CMAKE_CURRENT_LIST_DIR}/test/uri-test.c
	${CMAKE_CURRENT_LIST_DIR}/src/uriparser.c
)
