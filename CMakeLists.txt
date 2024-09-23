cmake_minimum_required(VERSION 3.5)

project(L_Sound LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE Include "include/*.h")
add_custom_target(_L_Sound_include SOURCES ${Include})

file(GLOB_RECURSE Sources "source/*.cpp")
add_library(L_Sound STATIC ${Sources})

target_include_directories(L_Sound PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/../L_Utility/include"
                            "${PROJECT_SOURCE_DIR}/../L_Variable/include"
                            "${PROJECT_SOURCE_DIR}/../LEti_Engine/include"
                            "${PROJECT_SOURCE_DIR}/../LEti_Engine/OpenGL/GLM"
)
