#include "SelectionSort.hpp"
#include "SwapBars.hpp"

void SelectionSort( SDL_Renderer* renderer, std::array<SDL_Rect, SCREEN_WIDTH> &bars, int n )
{
    for( int i = 0; i < n-1; i++ )
    {
        int min = i;

        for( int j = i+1; j < n; j++ )
            if( bars[j].h < bars[min].h )
                min = j;
        
        if( min != i )
        {
            SwapBars( &bars[i], &bars[min] );
            ClearScreen( renderer );
            DrawBars( renderer, bars, n );
        }
    }
}