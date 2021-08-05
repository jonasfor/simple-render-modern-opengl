cmake_minimum_required(VERSION 3.6)

PROJECT( modern_gl )

if(UNIX)

find_package(SDL2 REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED STATIC)

include_directories(${SDL_INCLUDE_DIRS})

endif()

if(WIN32)

include_directories(../include)
link_directories(../bin/x64)
endif()

if(ANDROID)

add_library(SDL2 IMPORTED SHARED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION /home/Randy/Android/native-source/org.libsdl/apps/libs/armeabi-v7a/libSDL2.so)
add_library(SDL2 IMPORTED SHARED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION /home/Randy/Android/native-source/org.libsdl/apps/libs/armeabi-v7a/libSDL2.so)
add_library(SDL2_image IMPORTED SHARED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION /home/Randy/Android/native-source/org.libsdl/apps/libs/armeabi-v7a/libSDL2_image.so)

endif()

set(EXECUTABLE_OUTPUT_PATH /home/jonas/Mynotes/ModernOpenGl)

file(GLOB SRCS *.cpp)
ADD_EXECUTABLE(modern_gl ${SRCS})
target_compile_options(modern_gl PUBLIC -Wpedantic  )
if(WIN32)
target_link_libraries(modern_gl PUBLIC SDL2.lib SDL2main.lib SDL2_image.lib  ${OPENGL_LIBRARIES}  ${GLEW_LIBRARY})
endif()
if(UNIX)
target_link_libraries(modern_gl PUBLIC ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} SDL2.so SDL2_image.so )
endif()

