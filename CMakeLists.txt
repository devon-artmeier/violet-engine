cmake_minimum_required(VERSION 3.16)
project(violet-engine LANGUAGES C CXX)

list(APPEND VIOLET_SRC
    "dependencies/glad/glad.c"
    "source/violet_audio.cpp"
    "source/violet_audio_miniaudio.c"
    "source/violet_core.cpp"
    "source/violet_file.cpp"
    "source/violet_main.cpp"
    "source/violet_math.cpp"
    "source/violet_mesh.cpp"
    "source/violet_matrix.cpp"
    "source/violet_message.cpp"
    "source/violet_resource.cpp"
    "source/violet_shader.cpp"
    "source/violet_sprite.cpp"
    "source/violet_texture.cpp"
    "source/violet_video.cpp"
    "source/violet_window.cpp"
    "dependencies/stb/stb_vorbis.c"
)

add_library(violet-engine STATIC ${VIOLET_SRC})

target_compile_definitions(violet-engine PRIVATE $<$<CONFIG:Debug>:VIOLET_DEBUG>)

find_package(SDL3 QUIET)
if(SDL3_FOUND)
    target_link_libraries(violet-engine PRIVATE SDL3::SDL3)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/dependencies/SDL/CMakeLists.txt")
    add_subdirectory("dependencies/SDL")
    target_include_directories(violet-engine PRIVATE "dependencies/SDL/include")
    target_link_libraries(violet-engine PRIVATE SDL3::SDL3)
endif()

find_package(glm QUIET)
if (GLM_FOUND)
    target_link_libraries(violet-engine PRIVATE glm::glm)
elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/dependencies/glm/CMakeLists.txt")
    add_subdirectory("dependencies/glm")
    target_include_directories(violet-engine PRIVATE "dependencies/glm")
    target_link_libraries(violet-engine PRIVATE glm::glm)
endif()

target_include_directories(violet-engine PRIVATE "include")
target_include_directories(violet-engine PRIVATE "dependencies/glad")
target_include_directories(violet-engine PRIVATE "dependencies/miniaudio")
target_include_directories(violet-engine PRIVATE "dependencies/stb")