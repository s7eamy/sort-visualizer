#include "BubbleSort.hpp"
#include "SwapBars.hpp"
#include "Drawing.hpp"

void BubbleSort( std::array<SDL_Rect, SCREEN_WIDTH> &arr, int n, SDL_Renderer* rend )
{
    for( int i = 0; i < n-1; i++ )
        for( int j = i+1; j < n; j++ )
            if( arr[i].h > arr[j].h )
            {
                SwapBars( &arr[i], &arr[j] );
                ClearScreen( rend );
                DrawBars( rend, arr, n );
            }
}
