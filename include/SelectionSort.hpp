#include <SDL2/SDL.h>
#include "ScreenDims.hpp"
#include <array>
#include "Drawing.hpp"

void SelectionSort( SDL_Renderer* renderer, std::array<SDL_Rect, SCREEN_WIDTH> &bars, int n );