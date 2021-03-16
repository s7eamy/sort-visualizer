#include "SwapBars.hpp"
#include <utility>

void SwapBars( SDL_Rect* rect1, SDL_Rect* rect2 )
{
    std::swap( rect1->h, rect2->h );
    std::swap( rect1->y, rect2->y );
}