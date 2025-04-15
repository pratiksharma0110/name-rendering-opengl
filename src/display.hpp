#pragma once

#include "../include/glad/glad.h"
#include <SDL2/SDL.h>

namespace Display {

constexpr int FPS = 60;
constexpr int FRAME_TARGET_TIME = 1000 / FPS;

extern SDL_Window *window;
extern int window_width;
extern int window_height;

bool initializeWindow();
void getOpenGLInfo();
void cleanUp();

} // namespace Display
