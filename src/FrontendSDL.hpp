#ifndef __SDL__FRONTEND_SDL_HPP__
#define __SDL__FRONTEND_SDL_HPP__

#include <SDL2/SDL.h>
#include <glad/glad.h>

class FrontendSDL {
private:
  SDL_Window* m_window;
  SDL_GLContext m_gl_context;

public:
  FrontendSDL(const char* title, int width, int height);
  ~FrontendSDL();

  void draw();

};

#endif
