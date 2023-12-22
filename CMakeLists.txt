cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# use ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache in ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(sfeMovie2 VERSION 1.0.0)

option(SFEMOVIE_BUILD_EXAMPLE "Build example program" TRUE)
option(SFEMOVIE_DYNAMIC_FFMPEG "Use dynamic FFmpeg" TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")

find_package(FFmpeg COMPONENTS avcodec avformat avutil swscale REQUIRED)
find_package(SFML 2.1 COMPONENTS audio graphics REQUIRED)

set(SOURCE_FILES
    src/sfeMovie/AudioStream.cpp
    src/sfeMovie/AudioStream.hpp
    src/sfeMovie/AVFunc.cpp
    src/sfeMovie/AVFunc.hpp
    src/sfeMovie/Demuxer.cpp
    src/sfeMovie/Demuxer.hpp
    src/sfeMovie/LoadLibrary.cpp
    src/sfeMovie/LoadLibrary.h
    src/sfeMovie/Movie.cpp
    src/sfeMovie/Movie.hpp
    src/sfeMovie/MovieImpl.cpp
    src/sfeMovie/MovieImpl.hpp
    src/sfeMovie/Stream.cpp
    src/sfeMovie/Stream.hpp
    src/sfeMovie/StreamSelection.hpp
    src/sfeMovie/Timer.cpp
    src/sfeMovie/Timer.hpp
    src/sfeMovie/TimerPriorities.hpp
    src/sfeMovie/VideoStream.cpp
    src/sfeMovie/VideoStream.hpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -stdlib=libc++)
    target_link_options(${PROJECT_NAME} PRIVATE -stdlib=libc++)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} PRIVATE ${FFmpeg_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FFmpeg_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PHYSFS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PHYSFS_LIBRARY} sfml-audio sfml-graphics)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if(SFEMOVIE_BUILD_EXAMPLE)
    add_executable(SFMLMoviePlayer example/SFMLMoviePlayer.cpp)
    target_link_libraries(SFMLMoviePlayer PRIVATE ${PROJECT_NAME})
endif()
