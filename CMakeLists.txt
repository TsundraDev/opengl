cmake_minimum_required(VERSION 3.28)

project(sdl)

set (SDL_SRC
  src/FrontendSDL.cpp
  src/GL_Program.cpp

  src/main.cpp
)

set (GLAD_SRC
  include/glad/glad.c
)

add_executable(sdl
  ${GLAD_SRC}
  ${SDL_SRC}
)
target_link_libraries(sdl SDL2)
include_directories(sdl include/glad)
include_directories(sdl include/)
include_directories(sdl src)
