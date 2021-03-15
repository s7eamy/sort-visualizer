#pragma once
#include <SDL2/SDL.h>
#include <array>
#include "ScreenDims.hpp"

void InsertionSort( std::array<SDL_Rect, SCREEN_WIDTH> &arr, int n, SDL_Renderer* rend );