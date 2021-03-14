#include <SDL2/SDL.h>
#include <array>
#include "ScreenDims.hpp"

void ClearScreen( SDL_Renderer* rend );
void DrawBars( SDL_Renderer* rend, std::array<SDL_Rect, SCREEN_WIDTH> arr, int n );
void ColorBars( SDL_Renderer* rend, std::array<SDL_Rect, SCREEN_WIDTH> arr, int n );
