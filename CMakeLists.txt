cmake_minimum_required(VERSION 3.16)
project(tools C)

set(CMAKE_C_STANDARD 99)
SET(GCC_COVERAGE_COMPILE_FLAGS "-mwindows")



add_executable(tools main.c REQUESTS/requests.c REQUESTS/requests.h GUI/windowsetup.c GUI/windowsetup.h GUI/handlers.c GUI/handlers.h GUI/widgets.h GUI/widgets.c)


FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

TARGET_LINK_LIBRARIES(tools ${GTK3_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)
target_link_libraries(${CMAKE_PROJECT_NAME} Iphlpapi.lib)






