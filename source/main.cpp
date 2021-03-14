/**
 * TODO:
 * 1. Implement more sorting algorithms (merge 3-way, heapsort, quicksort)
 * 2. Timer (DONE)
 * 3. Add sound fx
 * 4. Different configurations
 * 4.1. Randomization levels
 * 4.2. Element count
 */

//-------------------------------------------------
/* The includes needed for our program           */
#include <SDL2/SDL.h> /* the visualizer graphics */
#include <iostream>   /* std::cout and std::cin  */
#include <limits>     /* std::numeric_limits     */
#include <array>      /* for storing our bars    */
#include <chrono>     /* for measuring time      */
#include <algorithm>  /* std::sort               */
//-------------------------------------------------

//----------------------------
const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;
//----------------------------

//----------------------------------------------------------
// Forward declaration of all the functions we are going to use
bool Init( SDL_Window** win, SDL_Renderer** rend, int width );
void GetInput( int &n, int &t );
void ClearScreen( SDL_Renderer* rend );
void DrawBars( SDL_Renderer* rend, std::array<SDL_Rect, SCREEN_WIDTH> arr, int n );
void ColorBars( SDL_Renderer* rend, std::array<SDL_Rect, SCREEN_WIDTH> arr, int n );
void Kill( SDL_Renderer* rend, SDL_Window* win );
void SwapBars( SDL_Rect* rect1, SDL_Rect* rect2 );
// For mergesort
void MergeSort( const int num, SDL_Renderer* renderer, std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int high );
void Merge( std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int middle, int high );
//-----------------------------------------------

int main(int argc, char* args[])
{
    // input
    int num_of_elements;
    int sort_type = -1;
    GetInput( num_of_elements, sort_type );
    // creation of window
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Init( &window, &renderer, num_of_elements );
    // create the bars
    std::array<SDL_Rect, SCREEN_WIDTH> bars;
    for( int i = 0; i < num_of_elements; i++ )
    {
        int width = SCREEN_WIDTH/num_of_elements;
        int height = std::rand()%(SCREEN_HEIGHT-1) + 1;
        int x_pos = width*i;
        int y_pos = SCREEN_HEIGHT - height;
        bars[i] = {x_pos, y_pos, width, height};
    }
    DrawBars( renderer, bars, num_of_elements );
    // sorting
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    switch( sort_type )
    {
        case 1: /* bubble sort */
        for( int i = 0; i < num_of_elements-1; i++ )
        {
            for( int j = i+1; j < num_of_elements; j++ )
            {
                if( bars[i].h > bars[j].h )
                {
                    count++;
                    SwapBars( &bars[i], &bars[j] );
                    ClearScreen( renderer );
                    DrawBars( renderer, bars, num_of_elements );
                }
            }
        }
        break;

        case 2: /* selection sort */
        for( int i = 0; i < num_of_elements-1; i++ )
        {
            int min = i;

            for( int j = i+1; j < num_of_elements; j++ )
                if( bars[j].h < bars[min].h )
                    min = j;

            if( min != i )
            {
                count++;
                SwapBars( &bars[i], &bars[min] );
                ClearScreen( renderer );
                DrawBars( renderer, bars, num_of_elements );
            }
        }
        break;

        case 3: /* insertion sort */
        int hole_pos;
        int insert_value;

        for( int i = 0; i < num_of_elements; i++ )
        {
            insert_value = bars[i].h;
            hole_pos = i;

            while( hole_pos > 0 && bars[hole_pos-1].h > insert_value )
            {
                bars[hole_pos].h = bars[hole_pos-1].h;
                bars[hole_pos].y = bars[hole_pos-1].y;
                hole_pos -= 1;
            }

            bars[hole_pos].h = insert_value;
            bars[hole_pos].y = SCREEN_HEIGHT - bars[hole_pos].h;
            ClearScreen( renderer );
            DrawBars( renderer, bars, num_of_elements );
        }
        break;

        case 4: /* 2-way merge sort */
        MergeSort( num_of_elements, renderer, bars, 0, num_of_elements );
        ClearScreen( renderer );
        DrawBars( renderer, bars, num_of_elements );
        break;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    ClearScreen( renderer );
    ColorBars( renderer, bars, num_of_elements );
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    std::cout << '\n';
    std::cout << "RESULTS:\n";
    std::cout << "Algorithm took " << dur.count() << " milliseconds." << std::endl; 
    bool done = 0;
    SDL_Event e;
    while(!done)
    {
        while( SDL_PollEvent( &e ) > 0 )
        {
            if( e.type == SDL_QUIT )
            {
                done = 1;
            }
        }
    }
    return 0;
}
void MergeSort( const int num, SDL_Renderer* renderer, std::array<SDL_Rect, SCREEN_WIDTH> &arr, int low, int high )
{
    ClearScreen( renderer );
    DrawBars( renderer, arr, num );
    SDL_Delay( 5 );
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

void SwapBars( SDL_Rect* rect1, SDL_Rect* rect2 )
{
    std::swap( rect1->h, rect2->h );
    std::swap( rect1->y, rect2->y );
}

// gets input from STDIN
void GetInput( int &n, int &t )
{
    std::cout << "Input number of elements:\n";
    while(!(std::cin >> n) || (n < 0 || n > 1280) )
    {
        std::cout << "Bad input! Input number of elements again:\n";
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }
    /* ask for which sort to use */
    std::cout << "Which sort to use? Input the number:\n";
    std::cout << "1. Bubble Sort [ COMPLEXITY: O(n^2) ]\n";
    std::cout << "2. Selection Sort [ COMPLEXITY: O(n^2) ]\n";
    std::cout << "3. Insertion sort [ COMPLEXITY: O(n^2) ]\n";
    std::cout << "4. Merge Sort [ COMPLEXITY: O(n log(n)) ]\n";
    std::cout << "COMPLEXITY INFO IS TAKEN FROM https://www.bigocheatsheet.com \n";
    while(!(std::cin >> t) || (t < 1 || t > 4) )
    {
        std::cout << "Bad input! Input sort number again:\n";
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }
}

// destroys window & renderer, quits SDL subsystems
void Kill( SDL_Renderer* rend, SDL_Window* win )
{
    SDL_DestroyRenderer( rend );
    rend = nullptr;
    SDL_DestroyWindow( win );
    win = nullptr;
    SDL_Quit();
}

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
    }
    SDL_RenderPresent( rend );
}

// initialize window, renderer, sdl subsystems
bool Init( SDL_Window** win, SDL_Renderer** rend, int width)
{
    if( SDL_Init( SDL_INIT_VIDEO ) )
    {
        std::cout << "err1\n";
        return false;
    }
    *win = SDL_CreateWindow( "Sorting Algo Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP );
    if( !win )
    {
        std::cout << "err2\n";
        return false;
    }
    *rend = SDL_CreateRenderer( *win, -1, SDL_RENDERER_ACCELERATED );
    if( !rend )
    {
        std::cout << "err3\n";
        return false;
    }
    
    SDL_SetRenderDrawColor( *rend, 0, 0, 0, 255 );
    SDL_RenderClear( *rend );
    SDL_RenderPresent( *rend );

    return true;
}