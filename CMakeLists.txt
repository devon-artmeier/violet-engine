cmake_minimum_required(VERSION 3.16)
project(violet-engine LANGUAGES C CXX)

list(APPEND VIOLET_SRC
	"source/glad/glad.c"
	"source/violet_core.cpp"
	"source/violet_main.cpp"
	"source/violet_message.cpp"
)

add_library(violet-engine STATIC ${VIOLET_SRC})

target_compile_definitions(violet-engine PRIVATE VIOLET_DEBUG=$<CONFIG:Debug>)

find_package(SDL3 QUIET)
if(SDL3_FOUND)
	target_link_libraries(violet-engine PRIVATE SDL3::SDL3)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/dependencies/SDL/CMakeLists.txt")
	add_subdirectory("dependencies/SDL")
	target_include_directories(violet-engine PRIVATE "dependencies/SDL/include")
	target_link_libraries(violet-engine PRIVATE SDL3::SDL3)
else()
	message(FATAL_ERROR "\nSDL3 not found! Please initialize the submodules or download SDL3 and put the files in \"dependencies/SDL\"\nhttps://github.com/libsdl-org/SDL")
endif()

target_include_directories(violet-engine PRIVATE "include")
target_include_directories(violet-engine PRIVATE "dependencies/stb")
target_include_directories(violet-engine PRIVATE "dependencies/dr_libs")