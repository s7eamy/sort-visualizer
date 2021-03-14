#include <SDL2/SDL.h>
#include "MergeSort.hpp"
#include "ScreenDims.hpp"
#include "Drawing.hpp"


void MergeSort( const int num, SDL_Renderer* renderer, std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int high )
{
    ClearScreen( renderer );
    DrawBars( renderer, arr, num );
    if( low < high )
    {
        int middle = low + (high-low)/2;
        MergeSort( num, renderer, arr, low, middle );
        MergeSort( num, renderer, arr, middle+1, high );
        Merge( arr, low, middle, high );
    }
}
void Merge( std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int middle, int high )
{
    std::array<SDL_Rect, SCREEN_WIDTH> helper;
    for( int i = low; i <= high; i++ )
    {
        helper[i] = arr[i];
    }

    int i = low;
    int j = middle+1;
    int k = low;
    while( i <= middle && j <= high )
    {
        if( helper[i].h <= helper[j].h )
        {
            arr[k].y = helper[i].y;
            arr[k].h = helper[i].h;
            i++;
        }
        else
        {
            arr[k].h = helper[j].h;
            arr[k].y = helper[j].y;
            j++;
        }
        k++;
    }

    while( i <= middle )
    {
        arr[k].h = helper[i].h;
        arr[k].y = helper[i].y;
        k++;
        i++;
    }
}