#include "display.hpp"
#include "letter.hpp"
#include <string>
#include <vector>

bool isRunning = false;
int previousFrameTime = 0;

GLuint vertexShader = 0;
GLuint fragmentShader = 0;

GLuint shaderProgram = 0;

// letters
Letter *letterP = nullptr;
Letter *letterR = nullptr;
Letter *letterA = nullptr;
Letter *letterT = nullptr;
Letter *letterK = nullptr;
Letter *letterI = nullptr;

std::vector<Letter *> letters;

std::string vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

std::string fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n";

void clean() {
  delete letterI;
  delete letterT;
}

void initLetters() {
  GLfloat spacing = 0.1f;
  GLfloat barWidth = 0.04f;
  GLfloat totalHeight = -0.4f;
  GLfloat topBarLength = 0.12f;

  GLfloat startY = 0.2f;
  GLfloat midY = startY + totalHeight / 2.0f;

  // p
  GLfloat startX_P = -0.8f;
  std::vector<GLfloat> verticesP = {
      //  vbar
      startX_P, startY, 0.0f, startX_P + barWidth, startY, 0.0f,
      startX_P + barWidth, startY + totalHeight, 0.0f, startX_P,
      startY + totalHeight, 0.0f,
      //  thbar
      startX_P + barWidth, startY, 0.0f, startX_P + topBarLength, startY, 0.0f,
      startX_P + topBarLength, startY - barWidth, 0.0f, startX_P + barWidth,
      startY - barWidth, 0.0f,
      // mid hbar
      startX_P + barWidth, midY, 0.0f, startX_P + topBarLength, midY, 0.0f,
      startX_P + topBarLength, midY - barWidth, 0.0f, startX_P + barWidth,
      midY - barWidth, 0.0f,
      // r vbar
      startX_P + topBarLength - barWidth, startY, 0.0f, startX_P + topBarLength,
      startY, 0.0f, startX_P + topBarLength, midY - barWidth, 0.0f,
      startX_P + topBarLength - barWidth, midY - barWidth, 0.0f};
  std::vector<GLuint> indicesP = {0, 1, 2,  2,  3,  0, 4,  5,  6,  6,  7,  4,
                                  8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12};
  letters.push_back(new Letter(verticesP, indicesP));
  // r
  GLfloat startX_R = startX_P + topBarLength + spacing;
  std::vector<GLfloat> verticesR = {
      // vbar
      startX_R, startY, 0.0f, startX_R + barWidth, startY, 0.0f,
      startX_R + barWidth, startY + totalHeight, 0.0f, startX_R,
      startY + totalHeight, 0.0f,
      // t h bar
      startX_R + barWidth, startY, 0.0f, startX_R + topBarLength, startY, 0.0f,
      startX_R + topBarLength, startY - barWidth, 0.0f, startX_R + barWidth,
      startY - barWidth, 0.0f,
      // mid h bar
      startX_R + barWidth, midY, 0.0f, startX_R + topBarLength, midY, 0.0f,
      startX_R + topBarLength, midY - barWidth, 0.0f, startX_R + barWidth,
      midY - barWidth, 0.0f,
      // tr vertical bar
      startX_R + topBarLength - barWidth, startY, 0.0f, startX_R + topBarLength,
      startY, 0.0f, startX_R + topBarLength, midY - barWidth, 0.0f,
      startX_R + topBarLength - barWidth, midY - barWidth, 0.0f,
      // diagonal leg
      startX_R + barWidth, midY - barWidth, 0.0f, startX_R + topBarLength,
      totalHeight + startY, 0.0f, startX_R + topBarLength - barWidth,
      totalHeight + startY, 0.0f, startX_R + barWidth, midY - 2 * barWidth,
      0.0f};
  std::vector<GLuint> indicesR = {0,  1,  2,  2,  3,  0,  4,  5,  6,  6,
                                  7,  4,  8,  9,  10, 10, 11, 8,  12, 13,
                                  14, 14, 15, 12, 16, 17, 18, 18, 19, 16};
  letters.push_back(new Letter(verticesR, indicesR));

  // a
  GLfloat startX_A = startX_R + topBarLength + spacing;
  GLfloat peakY_A = startY;
  GLfloat baseY_A = startY + totalHeight;
  GLfloat crossY_A = (peakY_A + baseY_A) / 2.0f;
  GLfloat legWidth_A = barWidth;
  GLfloat legHeight_A = peakY_A - baseY_A;
  GLfloat legLength_A = 0.15f;
  GLfloat legSlant_A = legLength_A / legHeight_A * legWidth_A;
  GLfloat crossLength_A = 0.1f;

  std::vector<GLfloat> verticesA = {
      // left leg
      startX_A, baseY_A, 0.0f, startX_A + legSlant_A, baseY_A, 0.0f,
      startX_A + legLength_A, peakY_A, 0.0f,
      startX_A + legLength_A - legSlant_A, peakY_A, 0.0f,
      // right leg
      startX_A + legLength_A + spacing, baseY_A, 0.0f,
      startX_A + legLength_A + legSlant_A + spacing, baseY_A, 0.0f,
      startX_A + legLength_A + legSlant_A / 2.0f, peakY_A, 0.0f,
      startX_A + legLength_A - legSlant_A / 2.0f, peakY_A, 0.0f,
      // middle bar
      startX_A + legLength_A / 2.0f - crossLength_A / 2.0f, crossY_A, 0.0f,
      startX_A + legLength_A / 2.0f + crossLength_A / 2.0f, crossY_A, 0.0f,
      startX_A + legLength_A / 2.0f + crossLength_A / 2.0f, crossY_A - barWidth,
      0.0f, startX_A + legLength_A / 2.0f - crossLength_A / 2.0f,
      crossY_A - barWidth, 0.0f};
  std::vector<GLuint> indicesA = {0, 1, 2, 2, 3, 0,  4,  5,  6,
                                  6, 7, 4, 8, 9, 10, 10, 11, 8};
  letters.push_back(new Letter(verticesA, indicesA));

  // t
  GLfloat startX_T = startX_A + legLength_A + legLength_A + spacing * 2;
  GLfloat topBar_T = 0.16f;

  std::vector<GLfloat> verticesT = {
      // top bar
      startX_T, startY, 0.0f, startX_T + topBar_T, startY, 0.0f,
      startX_T + topBar_T, startY - barWidth, 0.0f, startX_T, startY - barWidth,
      0.0f,
      // cenn vertical bar
      startX_T + topBar_T / 2.0f - barWidth / 2.0f, startY, 0.0f,
      startX_T + topBar_T / 2.0f + barWidth / 2.0f, startY, 0.0f,
      startX_T + topBar_T / 2.0f + barWidth / 2.0f, startY + totalHeight, 0.0f,
      startX_T + topBar_T / 2.0f - barWidth / 2.0f, startY + totalHeight, 0.0f};
  std::vector<GLuint> indicesT = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};
  letters.push_back(new Letter(verticesT, indicesT));

  // i
  GLfloat startX_I = startX_T + topBar_T + spacing;

  std::vector<GLfloat> verticesI = {
      // top bar
      startX_I, startY, 0.0f, startX_I + topBarLength, startY, 0.0f,
      startX_I + topBarLength, startY - barWidth, 0.0f, startX_I,
      startY - barWidth, 0.0f,
      // bottom bar
      startX_I, startY + totalHeight + barWidth, 0.0f, startX_I + topBarLength,
      startY + totalHeight + barWidth, 0.0f, startX_I + topBarLength,
      startY + totalHeight, 0.0f, startX_I, startY + totalHeight, 0.0f,
      // center vertical bar
      startX_I + topBarLength / 2.0f - barWidth / 2.0f, startY - barWidth, 0.0f,
      startX_I + topBarLength / 2.0f + barWidth / 2.0f, startY - barWidth, 0.0f,
      startX_I + topBarLength / 2.0f + barWidth / 2.0f, startY + totalHeight,
      0.0f, startX_I + topBarLength / 2.0f - barWidth / 2.0f,
      startY + totalHeight, 0.0f};
  std::vector<GLuint> indicesI = {0, 1, 2, 2, 3, 0,  4,  5,  6,
                                  6, 7, 4, 8, 9, 10, 10, 11, 8};
  letters.push_back(new Letter(verticesI, indicesI));

  //   k
  GLfloat startX_K = startX_I + topBarLength + spacing;
  GLfloat cross_Y1 = midY;
  GLfloat cross_Y2 = startY + totalHeight;

  std::vector<GLfloat> verticesK = {
      // v bar
      startX_K, startY, 0.0f, startX_K + barWidth, startY, 0.0f,
      startX_K + barWidth, startY + totalHeight, 0.0f, startX_K,
      startY + totalHeight, 0.0f,
      // updiagonal
      startX_K + barWidth, midY, 0.0f, startX_K + topBarLength, startY, 0.0f,
      startX_K + topBarLength - barWidth, startY, 0.0f, startX_K + barWidth,
      midY - barWidth, 0.0f,
      // lower diagonal
      startX_K + barWidth, midY - barWidth, 0.0f, startX_K + topBarLength,
      totalHeight + startY, 0.0f, startX_K + topBarLength - barWidth,
      totalHeight + startY, 0.0f, startX_K + barWidth, midY - 2 * barWidth,
      0.0f};
  std::vector<GLuint> indicesK = {0, 1, 2, 2, 3, 0,  4,  5,  6,
                                  6, 7, 4, 8, 9, 10, 10, 11, 8};
  letters.push_back(new Letter(verticesK, indicesK));
}

GLuint compileShader(GLuint type, std::string &source) {
  const char *src = source.c_str();

  GLuint shaderObj = glCreateShader(type);
  glShaderSource(shaderObj, 1, &src, NULL);
  glCompileShader(shaderObj);

  return shaderObj;
}
void createShaderProgram(std::string &vShaderSource,
                         std::string &fShaderSource) {

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vShaderSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fShaderSource);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void graphicsPipeline() {
  createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void setup() {
  initLetters();
  graphicsPipeline();
}

void processInput() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;

  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_q) {
      isRunning = false;
      break;
    }
    break;

  default:
    break;
  }
}

void update() {

  // fps
  int timeToWait =
      Display::FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

  if (timeToWait > 0 && timeToWait <= Display::FRAME_TARGET_TIME) {
    SDL_Delay(timeToWait);
  }

  previousFrameTime = SDL_GetTicks();
}

void render() {
  glViewport(0, 0, Display::window_width, Display::window_height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);
  for (auto &letter : letters) {
    letter->draw();
  }

  SDL_GL_SwapWindow(Display::window);
}

int main() {
  isRunning = Display::initializeWindow();

  setup();

  while (isRunning) {
    processInput();
    update();
    render();
  }

  clean();
  Display::cleanUp();

  return 0;
}
