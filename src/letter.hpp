#pragma once
#include "../include/glad/glad.h"
#include <vector>

class Letter {
public:
  Letter(const std::vector<GLfloat> &vertices,
         const std::vector<GLuint> &indices);
  ~Letter();

  void draw();
  void updateBuffers(const std::vector<GLfloat> &vertices,
                     const std::vector<GLuint> &indices);

private:
  GLuint VAO, VBO, EBO;
  GLsizei indexCount;

  void setupBuffers(const std::vector<GLfloat> &vertices,
                    const std::vector<GLuint> &indices);
};
