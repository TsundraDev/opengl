#include "GL_Program.hpp"

#include <cassert>

GL_Program::GL_Program() :
  m_program(glCreateProgram()),
  m_shaders(std::vector<GLuint>()) {
  
}

bool GL_Program::attachShader(const char* filename, GLenum shader_type) {
  // Compile shader
  GLuint shader = glCreateShader(shader_type);

  char* shader_src = (char*) SDL_LoadFile(filename, nullptr);
  glShaderSource(shader, 1, &shader_src, nullptr);
  SDL_free(shader_src);

  glCompileShader(shader);


  // Error checking
  int shader_compile_check;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compile_check);

  if (!shader_compile_check) {
    fprintf(stderr, "GL_Program - Error compiling shader %s\n", filename);

    // Get more information
    int info_log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

    char* info_log = (char*) malloc(info_log_length);
    if (info_log == nullptr) {
      fprintf(stderr, "    Error getting error message\n");
      glDeleteShader(shader);
      return false;
    }


    glGetShaderInfoLog(shader, info_log_length, nullptr, info_log);
    fprintf(stderr, "    %s\n", info_log);

    free(info_log);
    glDeleteShader(shader);
    return false;
  }

  m_shaders.push_back(shader);

  return true;
}

bool GL_Program::link() {
  // Link program
  for (int i = 0; i < m_shaders.size(); i++) {
    glAttachShader(m_program, m_shaders[i]);
  }
  glLinkProgram(m_program);

  // Error checking
  int program_link_check;
  glGetProgramiv(m_program, GL_LINK_STATUS, &program_link_check);

  if (!program_link_check) {
    fprintf(stderr, "GL_Program - Error linking program\n");

    // Get more information
    int info_log_length;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &info_log_length);

    char* info_log = (char*) malloc(info_log_length);
    if (info_log == nullptr) {
      fprintf(stderr, "    Error getting error message\n");
      return false;
    }

    glGetProgramInfoLog(m_program, info_log_length, nullptr, info_log);
    fprintf(stderr, "    %s\n", info_log);

    free(info_log);
    return false;
  }


  // Cleanup shader list
  for (int i = 0; i < m_shaders.size(); i++) {
    glDeleteShader(m_shaders[i]);
  }
  m_shaders.clear();

  return true;
}

GL_Program::~GL_Program() {
assert(m_shaders.empty());

  glDeleteProgram(m_program);
}


