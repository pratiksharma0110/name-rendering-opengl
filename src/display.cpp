#include "display.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>

namespace Display {

SDL_Window *window = nullptr;
SDL_GLContext context = nullptr;

int window_width = 600;
int window_height = 800;

void getOpenGLInfo() {
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *vendor = glGetString(GL_VENDOR);

  if (version && renderer && vendor) {
    std::cout << "VERSION: " << version << "\n"
              << "RENDERER: " << renderer << "\n"
              << "VENDOR: " << vendor << "\n";
  } else {
    std::cerr << "Failed to get OpenGL information. Make sure everything is "
                 "set up.\n";
  }
}

bool initializeWindow() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL failed to initialize: " << SDL_GetError() << "\n";
    return false;
  }

  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  window_width = dm.w;
  window_height = dm.h;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, window_width,
                            window_height, SDL_WINDOW_OPENGL);

  if (!window) {
    std::cerr << "Failed to create window: " << SDL_GetError() << "\n";
    return false;
  }

  context = SDL_GL_CreateContext(window);
  if (!context) {
    std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << "\n";
    return false;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "glad was not initialized\n";
    return false;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  getOpenGLInfo();

  return true;
}

void cleanUp() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

} // namespace Display
