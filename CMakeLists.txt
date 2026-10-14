cmake_minimum_required(VERSION 3.20)
project(PolyUtilsProject LANGUAGES CXX)

add_library(PolyUtils src/PolyUtils.cpp)   # тип визначає BUILD_SHARED_LIBS
target_include_directories(PolyUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(PolyUtils PUBLIC cxx_std_20)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(PolyUtils PRIVATE POLYUTILS_EXPORTS)
else()
    target_compile_definitions(PolyUtils PUBLIC POLYUTILS_STATIC)
endif()

add_subdirectory(App)