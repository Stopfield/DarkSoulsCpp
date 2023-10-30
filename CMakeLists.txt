cmake_minimum_required( VERSION 3.22.1 )

project( DarkSoulsCPP )

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable( DarkSoulsCPP.exe ${SOURCE_FILES} )
