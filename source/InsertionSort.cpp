#include "InsertionSort.hpp"
#include "Drawing.hpp"

void InsertionSort( std::array<SDL_Rect, SCREEN_WIDTH> &arr, int n, SDL_Renderer* rend )
{
    int hole_pos;
    int insert_value;

    for( int i = 0; i < n; i++ )
    {
        insert_value = arr[i].h;
        hole_pos = i;

        while( hole_pos > 0 && arr[hole_pos-1].h > insert_value )
        {
            arr[hole_pos].h = arr[hole_pos-1].h;
            arr[hole_pos].y = arr[hole_pos-1].y;
            hole_pos -= 1;
        }

        arr[hole_pos].h = insert_value;
        arr[hole_pos].y = SCREEN_HEIGHT - arr[hole_pos].h;
        ClearScreen( rend );
        DrawBars( rend, arr, n );
    }
}