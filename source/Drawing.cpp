#include <SDL2/SDL.h>
#include "Drawing.hpp"
#include <array>

// makes the screen black
void ClearScreen( SDL_Renderer* rend )
{
    SDL_SetRenderDrawColor( rend, 0, 0, 0, 255 );
    SDL_RenderClear( rend );
}

// draw bars from the array
void DrawBars( SDL_Renderer* rend, std::array<SDL_Rect, SCREEN_WIDTH> arr, int n )
{
    SDL_SetRenderDrawColor( rend, 255, 255, 255, 255 );
    for( int i = 0; i < n; i++ ) 
    {
        SDL_RenderFillRect( rend, &arr[i] );
    }
    SDL_RenderPresent( rend );
}

// color the bars green
void ColorBars( SDL_Renderer* rend, std::array<SDL_Rect, SCREEN_WIDTH> arr, int n )
{
    SDL_SetRenderDrawColor( rend, 0, 255, 0, 255 );
    for( int i = 0; i < n; i++ ) 
    {
        SDL_RenderFillRect( rend, &arr[i] );
        SDL_RenderPresent( rend );
    }
}