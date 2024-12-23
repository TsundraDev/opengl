#include "FrontendSDL.hpp"
#include "GL_Program.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

float vertex[] = {
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
   0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
   0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
  -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
  -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
};

unsigned int indices[] = {
  0, 1, 2,
  1, 2, 3,
  4, 5, 6,
  5, 6, 7,
  0, 1, 4,
  1, 4, 5,
  2, 3, 6,
  3, 6, 7,
  0, 2, 4,
  2, 4, 6,
  1, 3, 5,
  3, 5, 7
};

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view  = glm::mat4(1.0f);
glm::mat4 proj  = glm::mat4(1.0f);


int main() {

  // Initialise matrix data
  float camY = 0;
  float phi = 0;
  view = glm::lookAt(glm::vec3(5.0f * cos(phi), camY, 5.0f * sin(phi)),
                      glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, 1.0f, 0.0f));
  proj = glm::perspective(glm::radians(45.0f), 8.0f/6.0f, 0.1f, 100.0f);


  // Create window
  FrontendSDL window = FrontendSDL("SDL Tutorial", 800, 600);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);

  // Program
  GL_Program prog = GL_Program();
  prog.attachShader("../src/shaders/vertex.glsl", GL_VERTEX_SHADER);
  prog.attachShader("../src/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
  prog.link();

  // VAO
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);


  // VBO, EBO
  GLuint vbo, ebo;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Setup Program data
  GLint pos_loc = glGetAttribLocation(prog.get(), "pos");
  GLint col_loc = glGetAttribLocation(prog.get(), "col");
  glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glVertexAttribPointer(col_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(pos_loc);
  glEnableVertexAttribArray(col_loc);

  GLint model_loc = glGetUniformLocation(prog.get(), "model");
  GLint view_loc = glGetUniformLocation(prog.get(), "view");
  GLint proj_loc = glGetUniformLocation(prog.get(), "proj");
  glUseProgram(prog.get());
  glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));
  glUseProgram(0);


  SDL_Event e;
  bool mainloop = true;
  while(mainloop) {
    while(SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        mainloop = false;
      }
    }
    const uint8_t* keyboard = SDL_GetKeyboardState(nullptr);
    if (keyboard[SDL_SCANCODE_W]) { camY += 0.1f; }
    if (keyboard[SDL_SCANCODE_S]) { camY -= 0.1f; }
    if (keyboard[SDL_SCANCODE_A]) { phi  += 0.05f; }
    if (keyboard[SDL_SCANCODE_D]) { phi  -= 0.05f; }

    view = glm::lookAt(glm::vec3(5.0f * cos(phi), camY, 5.0f * sin(phi)),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

    // Draw triangle
    glUseProgram(prog.get());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    window.draw();
  }

  // Unbind elements
  glUseProgram(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Destroy elements
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  return 0;
}
