cmake_minimum_required( VERSION 3.22.1 )

project( DarkSoulsCPP )

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable( DarkSoulsCPP.exe ${SOURCE_FILES} )

target_include_directories(DarkSoulsCPP.exe PRIVATE ${CMAKE_SOURCE_DIR}/headers)

