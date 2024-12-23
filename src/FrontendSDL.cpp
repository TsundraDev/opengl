#include "FrontendSDL.hpp"

#include <cstdio>
#include <cstdlib>

FrontendSDL::FrontendSDL(const char* title, int width, int height) :
  m_window(nullptr),
  m_gl_context(nullptr) {

  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "FrontendSDL - Unable to initialise SDL\n");
    exit(1);
  }

  // Create window
  m_window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_OPENGL);

  if (m_window == nullptr) {
    fprintf(stderr, "FrontendSDL - Unable to create window\n");
    SDL_Quit();
    exit(1);
  }

  // Setup OpenGL context
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  m_gl_context = SDL_GL_CreateContext(m_window);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    fprintf(stderr, "FrontendSDL - Unable to initialise GLAD\n");
  SDL_DestroyWindow(m_window);
    SDL_Quit();
    exit(1);
  }

  // Init first frame
  glViewport(0, 0, width, height);
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(m_window);
}

FrontendSDL::~FrontendSDL() {
  SDL_GL_DeleteContext(m_gl_context);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void FrontendSDL::draw() {
  SDL_GL_SwapWindow(m_window);
}
