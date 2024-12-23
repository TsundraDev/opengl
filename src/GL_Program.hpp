#ifndef __SDL__GL_PROGRAM_HPP__
#define __SDL__GL_PROGRAM_HPP__

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <vector>

class GL_Program {
private:
  GLuint m_program;
  std::vector<GLuint> m_shaders;

public:

  GL_Program();
  ~GL_Program();

  GLuint get() { return m_program; }

  bool attachShader(const char* filename, GLenum shader_type);
  bool link();

};

#endif
