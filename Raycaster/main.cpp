#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <thread>
#include "Vector2d.hpp"
#include "Bitmaps.cpp"

#define mapWidth 32
#define mapHeight 96

int worldMap[mapHeight][mapWidth] = {
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,-2,-2,-2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,-2,-2,-2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,-2,2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,3,0,0,0,0,0,0,0,0,0,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,-2,-2,-2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,-2,-2,-2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,-2,2,2,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,3,0,0,0,0,0,0,0,0,0,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,3,0,0,0,0,0,0,0,0,0,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
};

bool fullscreen = false;

double wallH = 4.0;

int textureWidth = 64;
int textureHeight = 64 * wallH;

int textureGranularity = 2;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void game_loop();

void update_screen();

void clear_screen();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

Uint32* pixels = NULL;

int pitch = NULL;

bool trapMouse = true;

double t = 0;
double lastTime = 0;
double frameTime = 0;
int fps = 0;

Vector2d pos = Vector2d(8, 12);
Vector2d dir = Vector2d(0, -1);
Vector2d cam = Vector2d(0.707, 0);
Vector2d box = Vector2d(22, 12); // Should always contain integers
Vector2d rayDir = Vector2d(0, 0);
Vector2d rayDistance = Vector2d(0, 0);
Vector2d sideToNextSide = Vector2d(0, 0);
Vector2d step = Vector2d(0, 0);
Vector2d lastPos = Vector2d(0, 0);
Vector2d floorWall = Vector2d(0, 0);

double orthDistance;
int hit = false;
bool vertical_side = false;
int wallHeight;
int wallTop;
int wallBottom;

double movementSpeed = 5;
double actualSpeed = movementSpeed;
bool forward = false;
bool backward = false;
bool right = false;
bool left = false;
bool sprint = false;

int yOffset = 0;
int maxYOffset = SCREEN_HEIGHT * 0.25;

//Main loop flag
bool quit = false;

int noice[SCREEN_WIDTH];
bool updateNoice = false;
bool sandNoice = false; // turns it off and on

int x_shift1; // removes bug causing vertical white lines when chaning textureGranularity
int x_shift2;

//Event handler
SDL_Event e;

bool init() {
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        //Create window
        window = SDL_CreateWindow( "RAYCASTER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        if( window == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    pitch = SCREEN_WIDTH * sizeof(Uint32);
    
    if (!success) printf( "Failed to initialize!\n" );
    return success;
}

void close() {
    delete[] pixels;
    // texture??
    
    //Destroy window
    //SDL_DestroyRenderer( renderer ); // TODO leak?
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    
    //readBMP("daggerfall_tpack/eridu200.bmp");
    
    //Start up SDL and create window
    if(init()) {
        game_loop();
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}

void raycast() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        
        box = Vector2d((int) pos.getX(), (int) pos.getY());
        
        rayDir = (cam * (2.0 * i / SCREEN_WIDTH - 1.0)) + dir;
        
        sideToNextSide = Vector2d(std::abs(1.0 / rayDir.getX()), std::abs(1.0 / rayDir.getY()));
        
        hit = false;
        
        if (rayDir.getX() < 0) {
            step = Vector2d(-1, 0);
            rayDistance = Vector2d((pos.getX() - box.getX()) * sideToNextSide.getX(), 0);
        } else {
            step = Vector2d(1, 0);
            rayDistance = Vector2d((box.getX() - pos.getX() + 1) * sideToNextSide.getX(), 0);
        }
        if (rayDir.getY() < 0) {
            step += Vector2d(0, -1);
            rayDistance += Vector2d(0, (pos.getY() - box.getY()) * sideToNextSide.getY());
        } else {
            step += Vector2d(0, 1);
            rayDistance += Vector2d(0, (box.getY() - pos.getY() + 1) * sideToNextSide.getY());
        }
        
        bool tooFar = false;
        
        //Digital Differential Analysis
        while (!hit) {
            if (rayDistance.getX() < rayDistance.getY()) {
                rayDistance += Vector2d(sideToNextSide.getX(), 0);
                box += Vector2d(step.getX(), 0);
                vertical_side = true;
                orthDistance = (box.getX() - pos.getX() + (1.0 - step.getX()) / 2.0) / rayDir.getX();
            } else {
                rayDistance += Vector2d(0, sideToNextSide.getY());
                box += Vector2d(0, step.getY());
                vertical_side = false;
                orthDistance = (box.getY() - pos.getY() + (1.0 - step.getY()) / 2.0) / rayDir.getY();
            }
            if (worldMap[(int) box.getY()][(int) box.getX()] > 0) {
                hit = worldMap[(int) box.getY()][(int) box.getX()];
            }
            else if (orthDistance > 30) {
                tooFar = true;
                break;
            }
        }
        
        /*
        if (vertical_side) {
            orthDistance = (box.getX() - pos.getX() + (1.0 - step.getX()) / 2.0) / rayDir.getX();
        } else {
            orthDistance = (box.getY() - pos.getY() + (1.0 - step.getY()) / 2.0) / rayDir.getY();
        }*/
        
        // this can be hardcoded if tooFar
        wallHeight = (int) (SCREEN_HEIGHT / orthDistance) * wallH;
        wallTop = (SCREEN_HEIGHT - wallHeight) / 2.0;
        //if (wallTop < 0) wallTop = 0;
        wallBottom = (SCREEN_HEIGHT + wallHeight) / 2.0;
        //if (wallBottom > SCREEN_HEIGHT) wallBottom = SCREEN_HEIGHT;
        
        double wallX; // where the wall was hit
        if (vertical_side) wallX = pos.getY() + rayDir.getY() * orthDistance;
        else wallX = pos.getX() + rayDir.getX() * orthDistance;
        wallX -= floor(wallX);
        
        int textureX = (int) (wallX * (double) textureWidth); // x cordinate in texture domain
        if ((vertical_side && rayDir.getX() > 0) or (!vertical_side && rayDir.getY() < 0)) textureX = textureWidth - textureX - 1;
        
        wallTop += yOffset;
        wallBottom += yOffset;
        
        int actualWallTop = wallTop;
        int actualWallBottom = wallBottom;
        
        if (wallTop < 0) wallTop = 0;
        if (wallBottom > SCREEN_HEIGHT) wallBottom = SCREEN_HEIGHT;
        
        /*if (textureIndex == 33) {
         // draws untextured wall
         if (vertical_side) SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
         else SDL_SetRenderDrawColor(renderer, red / 2, green / 2, blue / 2, 255);
         SDL_RenderDrawLine(renderer, i, wallTop, i, wallBottom);
         } else {*/
        
        if (true) {
            x_shift1 = (i + 1) % 2;
            x_shift2 = (i + 1) % 4;
            
            //SDL_SetRenderDrawColor(renderer, 40, 60, 70, 255);
            //SDL_RenderDrawLine(renderer, i, 0, i, wallTop);
            
            // draws floor
            //SDL_SetRenderDrawColor(renderer, 76, 70, 50, 255);
            //SDL_RenderDrawLine(renderer, i, wallBottom, i, SCREEN_HEIGHT);
            
            if (sandNoice) {
                SDL_SetRenderDrawColor(renderer, 55, 45, 40, 255);
                SDL_RenderDrawPoint(renderer, i, noice[i] + wallBottom);
                SDL_SetRenderDrawColor(renderer, 60, 55, 40, 255);
                SDL_RenderDrawPoint(renderer, i, noice[i] * 2 + wallBottom);
            }
            
            for (int y = wallTop - yOffset; y < wallBottom - yOffset; y++) {
                if (!tooFar) {
                    int d = y * 256 + (wallHeight - SCREEN_HEIGHT) * 128;
                    int textureY = ((d * textureHeight) / wallHeight) / 256;
                    Uint16 color;
                    switch (hit) {
                        case 1: {
                            color = t2[textureWidth * textureY + textureX];
                            break;
                        }
                        case 2: {
                            color = t1[textureWidth * textureY + textureX];
                            break;
                        }
                        case 3: {
                            color = t3[textureWidth * textureY + textureX];
                            break;
                        }
                        default: {
                            color = t0[textureWidth * textureY + textureX];
                            break;
                        }
                    }
                    
                    Uint8 c1 = (Uint8) (color >> 8);
                    Uint8 c2 = (Uint8) (color >> 4) & 0x0f;
                    Uint8 c3 = ((Uint8) (color) << 4);
                    c3 = c3 >> 4;
                    
                    if (!vertical_side) {
                        c1 = c1 << 4;
                        c2 = c2 << 4;
                        c3 = c3 << 4;
                    } else {
                        c1 = c1 << 3;
                        c2 = c2 << 3;
                        c3 = c3 << 3;
                    }
                    
                    // night
                    c1 -= c1 * orthDistance / 31;
                    c2 -= c2 * orthDistance / 31;
                    c3 -= c3 * orthDistance / 31;
                    
                    int r = std::sqrt((i - SCREEN_WIDTH / 2) * (i - SCREEN_WIDTH / 2) + (y + yOffset - SCREEN_HEIGHT / 2) * (y + yOffset - SCREEN_HEIGHT / 2)) + 30;
                    c1 = ((int) c1) * 50 / r;
                    c2 = ((int) c2) * 50 / r;
                    c3 = ((int) c3) * 50 / r;
                    
                    //SDL_SetRenderDrawColor(renderer, c1, c2, c3, 255);
                    //SDL_RenderDrawPoint(renderer, i, y + yOffset);
                    pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) 255) + (((Uint32) c3) << 8) + (((Uint32) c2) << 16) + (((Uint32) c1) << 24));
                } else pixels[(y + yOffset) * SCREEN_WIDTH + i] = 0;
            }
        }
        
        if (true) {
            
            if (vertical_side && rayDir.getX() > 0) floorWall = Vector2d(box.getX(), box.getY() + wallX);
            else if (vertical_side && rayDir.getX() < 0) floorWall = Vector2d(box.getX() + 1.0, box.getY() + wallX);
            else if (!vertical_side && rayDir.getY() > 0) floorWall = Vector2d(box.getX() + wallX, box.getY());
            else floorWall = Vector2d(box.getX() + wallX, box.getY() + 1.0);
            
            double currentDistance;
            
            /*for (int y = actualWallBottom - yOffset; y < SCREEN_HEIGHT + yOffset; y++) {
             currentDistance = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
             double weight = (currentDistance * wallH) / (orthDistance);
             Vector2d currentFloor = Vector2d(weight * floorWall.getX() + (1.0 - weight) * pos.getX(), weight * floorWall.getY() + (1.0 - weight) * pos.getY());
             if (worldMap[(int) currentFloor.getY()][(int) currentFloor.getX()] < 1) {
             Vector2d floorTexture = Vector2d((int) (currentFloor.getX() * textureWidth / 2) % textureWidth, (int) (currentFloor.getY() * textureHeight / 4) % textureHeight);
             Uint16 color_ceiling = t0[int(textureWidth * floorTexture.getY() + floorTexture.getX())];
             Uint8 c1_c = (Uint8) (color_ceiling >> 8);
             Uint8 c2_c = (Uint8) (color_ceiling >> 4) & 0x0f;
             Uint8 c3_c = ((Uint8) (color_ceiling) << 4);
             c3_c = c3_c >> 4;
             c1_c = c1_c << 4;
             c2_c = c2_c << 4;
             c3_c = c3_c << 4;
             pixels[(SCREEN_HEIGHT - y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) 255) + (((Uint32) c3_c) << 8) + (((Uint32) c2_c) << 16) + (((Uint32) c1_c) << 24));                    //SDL_SetRenderDrawColor(renderer, c1_c << 4, c2_c
             }
             }*/
            for (int y = actualWallBottom - yOffset; y < SCREEN_HEIGHT + yOffset; y++) {
                Uint8 c1_c = 0;
                Uint8 c2_c = 0;
                Uint8 c3_c = (y / 16);
                pixels[(SCREEN_HEIGHT - y + yOffset - 1) * SCREEN_WIDTH + i] = (((Uint32) 255) + (((Uint32) c3_c) << 8) + (((Uint32) c2_c) << 16) + (((Uint32) c1_c) << 24));
            }

            for (int y = wallBottom - yOffset; y < SCREEN_HEIGHT - yOffset; y++) {
                Uint8 c1_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10) * 2;
                Uint8 c2_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10) * 1.5;
                Uint8 c3_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10);
                pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) 255) + (((Uint32) c3_c) << 8) + (((Uint32) c2_c) << 16) + (((Uint32) c1_c) << 24));
            }
            
            /*for (int y = wallBottom - yOffset; y < SCREEN_HEIGHT - yOffset; y++) {
             currentDistance = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
             double weight = (currentDistance * wallH) / (orthDistance);
             Vector2d currentFloor = Vector2d(weight * floorWall.getX() + (1.0 - weight) * pos.getX(), weight * floorWall.getY() + (1.0 - weight) * pos.getY());
             if (worldMap[(int) currentFloor.getY()][(int) currentFloor.getX()] < 1) {
             Vector2d floorTexture = Vector2d((int) (currentFloor.getX() * textureWidth / 2) % textureWidth, (int) (currentFloor.getY() * textureHeight / 4) % textureHeight);
             Uint16 color_ceiling = t3[int(textureWidth * floorTexture.getY() + floorTexture.getX())];
             Uint8 c1_c = (Uint8) (color_ceiling >> 8);
             Uint8 c2_c = (Uint8) (color_ceiling >> 4) & 0x0f;
             Uint8 c3_c = ((Uint8) (color_ceiling) << 4);
             c3_c = c3_c >> 4;
             c1_c = c1_c << 4;
             c2_c = c2_c << 4;
             c3_c = c3_c << 4;
             pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) 255) + (((Uint32) c3_c) << 8) + (((Uint32) c2_c) << 16) + (((Uint32) c1_c) << 24));
             //SDL_SetRenderDrawColor(renderer, c1_c << 3, c2_c << 3, c3_c << 3, 255);
             //SDL_RenderDrawLine(renderer, i, y + yOffset, i, y + yOffset + 2);
             }
             }*/
            
        }
    }
}

void game_loop() {
    
    SDL_SetRelativeMouseMode(SDL_bool(trapMouse));
    
    //While application is running
    while( !quit ) {
        
        SDL_LockTexture(texture, NULL,(void**) &pixels, &pitch);
        
        if (updateNoice && sandNoice) {
            for (int i = 0; i < SCREEN_WIDTH; i++) noice[i] = rand() % (SCREEN_HEIGHT / 2);
        }
        
        x_shift1 = 0;
        x_shift2 = 0;
        
        raycast();
        
        lastTime = t;
        t = SDL_GetTicks();
        frameTime = (t - lastTime) / 1000.0;
        fps = (int) (1.0 / frameTime);
        std::cout << "FPS: " << fps << std::endl;
        update_screen();
        lastPos = pos.copy();
        if (sprint) actualSpeed = movementSpeed * 2;
        else actualSpeed = movementSpeed;
        if (forward) {
            Vector2d newPos = pos + dir.norm() * actualSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] <= 0) pos += dir.norm() * actualSpeed * frameTime;        }
        if (left) {
            Vector2d newPos = pos + dir.rotate(-3.14159 / 2).norm() * actualSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] <= 0) pos += dir.rotate(-3.14159 / 2).norm() * actualSpeed * frameTime;
        }
        if (backward) {
            Vector2d newPos = pos - dir.norm() * actualSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] <= 0) pos -= dir.norm() * actualSpeed * frameTime;
        }
        if (right) {
            Vector2d newPos = pos + dir.rotate(3.14159 / 2).norm() * actualSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] <= 0) pos += dir.rotate(3.14159 / 2).norm() * actualSpeed * frameTime;
        }
        
        updateNoice = false;
        
        if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY()) updateNoice = true;
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            
            else if( e.type == SDL_KEYDOWN ) {
                switch(e.key.keysym.sym) {
                    case SDLK_w: {
                        forward = true;
                        break;
                    }
                    case SDLK_a: {
                        left = true;
                        break;
                    }
                    case SDLK_s: {
                        backward = true;
                        break;
                    }
                    case SDLK_d: {
                        right = true;
                        break;
                    }
                    case SDLK_LSHIFT: {
                        sprint = true;
                        break;
                    }
                    case SDLK_ESCAPE: {
                        //trapMouse = !trapMouse;
                        //SDL_SetRelativeMouseMode(SDL_bool(trapMouse));
                        quit = true;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            
            else if( e.type == SDL_KEYUP ) {
                switch(e.key.keysym.sym) {
                    case SDLK_w: {
                        forward = false;
                        break;
                    }
                    case SDLK_a: {
                        left = false;
                        break;
                    }
                    case SDLK_s: {
                        backward = false;
                        break;
                    }
                    case SDLK_d: {
                        right = false;
                        break;
                    }
                    case SDLK_LSHIFT: {
                        sprint = false;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            
            else if( e.type == SDL_MOUSEMOTION) {
                updateNoice = true;
                int x, y;
                SDL_GetMouseState( &x, &y );
                dir.rotateThis(e.motion.xrel / 2000.0);
                cam.rotateThis(e.motion.xrel / 2000.0);
                yOffset -= e.motion.yrel / 2;
                if (yOffset > maxYOffset) yOffset = maxYOffset;
                else if (yOffset < -maxYOffset) yOffset = -maxYOffset;
            }
            
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                
            }
        }
    }
}

void update_screen() {
    SDL_UnlockTexture(texture);
    clear_screen();
    //SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent( renderer );
}

void clear_screen() {
    SDL_SetRenderDrawColor( renderer, 80, 48, 16, 0xFF );
    SDL_RenderClear( renderer );
}
