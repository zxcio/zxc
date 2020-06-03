cmake_minimum_required(VERSION 2.8.3)
project(zxc)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(FOUNDATION_LIBRARY Foundation)
endif()

find_package(PkgConfig)
pkg_check_modules(PC_LIBSERIALPORT libserialport)

## Sources
set(SRCS
    src/main.c
)

add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC
    src/include
    ${PC_LIBSERIALPORT_INCLUDE_DIRS}
)
target_link_directories(${PROJECT_NAME} PUBLIC
    ${PC_LIBSERIALPORT_LIBRARY_DIRS}
)
if(APPLE)
    target_link_libraries(${PROJECT_NAME}
        ${FOUNDATION_LIBRARY}
        ${IOKIT_LIBRARY}
        ${PC_LIBSERIALPORT_LIBRARIES}
    )
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} rt pthread)
else()
    target_link_libraries(${PROJECT_NAME} setupapi)
endif()
