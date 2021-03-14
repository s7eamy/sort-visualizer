#include <SDL2/SDL.h>
#include <array>
#include "ScreenDims.hpp"

void MergeSort( const int num, SDL_Renderer* renderer, std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int high );
void Merge( std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int middle, int high );