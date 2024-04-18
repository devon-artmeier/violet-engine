cmake_minimum_required(VERSION 3.16)
project(violet-engine LANGUAGES C CXX)

add_executable(violet-engine
	"source/main.cpp"
)

find_package(SDL3 QUIET)
if(SDL3_FOUND)
	target_link_libraries(violet-engine PRIVATE SDL3::SDL3)
elseif(EXISTS "dependencies/SDL/CMakeLists.txt")
	add_subdirectory("dependencies/SDL" EXCLUDE_FROM_ALL)
	target_include_directories(violet-engine PRIVATE "dependencies/SDL/include")
	target_link_libraries(violet-engine PRIVATE SDL3::SDL3-static)
else()
	message(FATAL_ERROR "\nSDL3 not found!\nPlease download it and put the files in dependencies/SDL\nhttps://github.com/libsdl-org/SDL")
endif()

target_include_directories(violet-engine PRIVATE "dependencies/stb")
target_include_directories(violet-engine PRIVATE "dependencies/dr_libs")