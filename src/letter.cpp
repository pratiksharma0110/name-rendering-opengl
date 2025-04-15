#include "letter.hpp"
#include "../include/glad/glad.h"

Letter::Letter(const std::vector<GLfloat> &vertices,
               const std::vector<GLuint> &indices) {
  setupBuffers(vertices, indices);
}
Letter::~Letter() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Letter::setupBuffers(const std::vector<GLfloat> &vertices,
                          const std::vector<GLuint> &indices) {
  indexCount = indices.size();

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
               vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Letter::updateBuffers(const std::vector<GLfloat> &vertices,
                           const std::vector<GLuint> &indices) {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  setupBuffers(vertices, indices);
}

void Letter::draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
