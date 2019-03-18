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

int wallH = 2;

int textureWidth = 128;
int textureHeight = 128 * wallH;

int textureGranularity = 2;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 360;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void game_loop();

void update_screen();

void clear_screen();

void animate_gun();

void drawDogs();

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

Uint32* pixels = NULL;

int pitch;

bool trapMouse = true;

double t = 0;
double lastTime = 0;
double frameTime = 0;
int fps = 0;

int gunSprite = 0;
int shootTime = 0;
bool shooting = false;

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
int maxYOffset = SCREEN_HEIGHT * 0.4;

//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;

SDL_Rect textureRenderSize;

struct Dog {
    double x;
    double y;
};

int zBuffer[SCREEN_WIDTH];

std::vector<Dog> dogs = {};

bool init() {
    
    for (int i = 1; i < 6; i++) {
        Dog d;
        d.x = i * 5;
        d.y = i * 7;
        dogs.push_back(d);
    }
    
    textureRenderSize.x = 0;
    textureRenderSize.y = 0;
    textureRenderSize.w = SCREEN_WIDTH * 2;
    textureRenderSize.h = SCREEN_HEIGHT * 2;
    
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
        window = SDL_CreateWindow( "RAYCASTER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2 + 120, SDL_WINDOW_SHOWN );
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
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
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
            
            Uint8 c1;
            Uint8 c2;
            Uint8 c3;
            
            Uint16 color;
            
            for (int y = wallTop - yOffset; y < wallBottom - yOffset; y++) {
                
                if (!tooFar) {
                    
                    int d = y * 256 + (wallHeight - SCREEN_HEIGHT) * 128;
                    int textureY = ((d * textureHeight) / wallHeight) / 256;
                    
                    if (textureWidth * textureY + textureX > textureWidth * textureHeight || textureWidth * textureY + textureX < 0) break; // prevents crashes
                    switch (hit) {
                        case 1: {
                            color = ice[textureWidth * textureY + textureX];
                            break;
                        }
                        case 2: {
                            color = ice2[textureWidth * textureY + textureX];
                            break;
                        }
                        case 3: {
                            color = skull[textureWidth * textureY + textureX];
                            break;
                        }
                        default: {
                            color = wood[textureWidth * textureY + textureX];
                            break;
                        }
                    }
                    
                    c1 = (Uint8) (color >> 8);
                    c2 = (Uint8) (color >> 4) & 0x0f;
                    c3 = ((Uint8) (color) << 4);
                    c3 = c3 >> 4; // todo
                    
                    if (!vertical_side) {
                        c1 = c1 << 4;
                        c2 = c2 << 4;
                        c3 = c3 << 4;
                    } else {
                        c1 = c1 << 3;
                        c2 = c2 << 3;
                        c3 = c3 << 3;
                    }
                    
                    c1 -= c1 * orthDistance / 31;
                    c2 -= c2 * orthDistance / 31;
                    c3 -= c3 * orthDistance / 31;
                    
                    //int r = std::sqrt((float)(i - SCREEN_WIDTH / 2) * (i - SCREEN_WIDTH / 2) + (y + yOffset - SCREEN_HEIGHT / 2) * (y + yOffset - SCREEN_HEIGHT / 2)) + 25;
                    int r = abs((i - SCREEN_WIDTH / 2)) + abs((y + yOffset - SCREEN_HEIGHT / 2)) + 25;
                    c1 = ((int) c1) * 50 / r;
                    c2 = ((int) c2) * 50 / r;
                    c3 = ((int) c3) * 50 / r;
                    
                    pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) c3) + (((Uint32) c2) << 8) + (((Uint32) c1) << 16) + (((Uint32) 255) << 24));
                } else pixels[(y + yOffset) * SCREEN_WIDTH + i] = 4278190080; // black
            }
        }
        
        if (true) {
            
            if (vertical_side && rayDir.getX() > 0) floorWall = Vector2d(box.getX(), box.getY() + wallX);
            else if (vertical_side && rayDir.getX() < 0) floorWall = Vector2d(box.getX() + 1.0, box.getY() + wallX);
            else if (!vertical_side && rayDir.getY() > 0) floorWall = Vector2d(box.getX() + wallX, box.getY());
            else floorWall = Vector2d(box.getX() + wallX, box.getY() + 1.0);
            
            Uint8 c1_c;
            Uint8 c2_c;
            Uint8 c3_c;
            
            for (int y = actualWallBottom - yOffset; y < SCREEN_HEIGHT + yOffset; y++) {
                c1_c = (y / 12);
                c2_c = 10;
                c3_c = (y / 10);
                pixels[(SCREEN_HEIGHT - y + yOffset - 1) * SCREEN_WIDTH + i] = (((Uint32) c3_c) + (((Uint32) c2_c) << 8) + (((Uint32) c1_c) << 16) + (((Uint32) 255) << 24));
            }

            for (int y = wallBottom - yOffset; y < SCREEN_HEIGHT - yOffset; y++) {
                c1_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10);
                c2_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10);
                c3_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10) * 1.4;
                pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) c3_c) + (((Uint32) c2_c) << 8) + (((Uint32) c1_c) << 16) + (((Uint32) 255) << 24));
            }
        }
        zBuffer[i] = orthDistance;
    }
}

void game_loop() {
    
    SDL_SetRelativeMouseMode(SDL_bool(trapMouse));
    
    int countFPS = 0;
    fps = 0;
    
    //While application is running
    while( !quit ) {
        
        SDL_LockTexture(texture, NULL,(void**) &pixels, &pitch);
        
        raycast();
        drawDogs();
        animate_gun();
        pixels[SCREEN_WIDTH * SCREEN_HEIGHT / 2 + SCREEN_WIDTH / 2] = 255 << 8; // reticle
        
        lastTime = t;
        t = SDL_GetTicks();
        frameTime = (t - lastTime) / 1000.0;
        fps += (int) (1.0 / frameTime);
        if (++countFPS > 30) {
            fps /= countFPS;
            countFPS = 0;
            std::cout << "FPS: " << fps << std::endl;
        }
        update_screen();
        lastPos = pos.copy();
        if (sprint) actualSpeed = movementSpeed * 5;
        else actualSpeed = movementSpeed;
        if (forward) {
            Vector2d newPos = pos + dir.norm() * actualSpeed * frameTime;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] <= 0) pos += dir.norm() * actualSpeed * frameTime;
            else {
                Vector2d delta = Vector2d(0, 0);
                // todo fungerar bara vid vinklar större än 45
                if ((int) newPos.getX() != (int) pos.getX() && abs(dir.getY()) > abs(dir.getX())) {
                    delta = Vector2d(0, dir.norm().getY())  * actualSpeed * frameTime;
                }
                else if ((int) newPos.getY() != (int) pos.getY()) {
                    delta = Vector2d(dir.norm().getX(), 0)  * actualSpeed * frameTime;
                }
                newPos = pos + delta * 5;
                if (worldMap[(int) newPos.getY()][(int) newPos.getX()] <= 0) pos += delta;
            }
        }
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
                        if (true) quit = true; // todo replace true
                        else {
                            trapMouse = !trapMouse;
                            SDL_SetRelativeMouseMode(SDL_bool(trapMouse));
                        }
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
                int x, y;
                SDL_GetMouseState( &x, &y );
                dir.rotateThis(e.motion.xrel / 2000.0);
                cam.rotateThis(e.motion.xrel / 2000.0);
                yOffset -= e.motion.yrel / 2;
                if (yOffset > maxYOffset) yOffset = maxYOffset;
                else if (yOffset < -maxYOffset) yOffset = -maxYOffset;
            }
            
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                gunSprite = 1;
                shooting = true;
                shootTime = SDL_GetTicks();
            }
        }
    }
}

void animate_gun() {
    Uint32 c;
    if (SDL_GetTicks() > shootTime + 100 && shooting) {
        gunSprite++;
        shootTime = SDL_GetTicks();
    }
    if (gunSprite > 4) {
        gunSprite = 0;
        shooting = false;
    }
    for (int i = 0; i < 64 * 64; i++) {
        switch (gunSprite) {
            case 0:
                c = pistol_ready[i];
                break;
            case 1:
                c = pistol_atk1[i];
                break;
            case 2:
                c = pistol_atk2[i];
                break;
            case 3:
                c = pistol_atk3[i];
                break;
            case 4:
                c = pistol_atk4[i];
                break;
            default:
                c = pistol_ready[i];
                break;
        }
        Uint8 c1 = (Uint8) (c >> 8);
        Uint8 c2 = (Uint8) (c >> 4) & 0x0f;
        Uint8 c3 = ((Uint8) (c) << 4);
        c3 = c3 >> 4;
        
        if (gunSprite == 2) {
            c1 = c1 << 4;
            c2 = c2 << 4;
            c3 = c3 << 4;
        } else {
            c1 = c1 << 3;
            c2 = c2 << 3;
            c3 = c3 << 3;
        }
        
        if (c != 0x0908) {
            for (int k = 0; k < 4; k++) {
                pixels[(SCREEN_HEIGHT - 256 + (i / 64) * 4) * SCREEN_WIDTH + (i * 4 + k) % 256 + SCREEN_WIDTH / 2 - 128] = (((Uint32) c3) + (((Uint32) c2) << 8) + (((Uint32) c1) << 16) + (((Uint32) 255) << 24));
                pixels[(SCREEN_HEIGHT - 256 + (i / 64) * 4 + 1) * SCREEN_WIDTH + (i * 4 + k) % 256 + SCREEN_WIDTH / 2 - 128] = (((Uint32) c3) + (((Uint32) c2) << 8) + (((Uint32) c1) << 16) + (((Uint32) 255) << 24));
                pixels[(SCREEN_HEIGHT - 256 + (i / 64) * 4 + 2) * SCREEN_WIDTH + (i * 4 + k) % 256 + SCREEN_WIDTH / 2 - 128] = (((Uint32) c3) + (((Uint32) c2) << 8) + (((Uint32) c1) << 16) + (((Uint32) 255) << 24));
                pixels[(SCREEN_HEIGHT - 256 + (i / 64) * 4 + 3) * SCREEN_WIDTH + (i * 4 + k) % 256 + SCREEN_WIDTH / 2 - 128] = (((Uint32) c3) + (((Uint32) c2) << 8) + (((Uint32) c1) << 16) + (((Uint32) 255) << 24));
            }
        }
    }
}

void drawDogs() {
    // todo sort the sprites
    for (int i = 0; i < dogs.size(); i++) {
        Vector2d dogPos = Vector2d(dogs[i].x, dogs[i].y);
        Vector2d newDogPos = dogPos + (pos - dogPos).norm() * 2 * frameTime;
        if ((pos - newDogPos).mag() > 2) {
            if (worldMap[(int) newDogPos.getY()][(int) newDogPos.getX()] <= 0) {
                dogs[i].x = newDogPos.getX();
                dogs[i].y = newDogPos.getY();
            }
        }
        // relative distance
        Vector2d spriteDistance = Vector2d(dogs[i].x - pos.getX(), dogs[i].y - pos.getY());
        double inverseDeterminant = 1.0 / (cam.getX() * dir.getY() - cam.getY() * dir.getX());
        Vector2d transformed = Vector2d(dir.getY() * spriteDistance.getX() - dir.getX() * spriteDistance.getY(), -cam.getY() * spriteDistance.getX() + cam.getX() * spriteDistance.getY());
        transformed *= inverseDeterminant;
        int spriteScreenX = int((SCREEN_WIDTH / 2) * (1 + transformed.getX() / transformed.getY()));
        int spriteHeight = abs(int(SCREEN_HEIGHT / transformed.getY()));
        int drawStartY = SCREEN_HEIGHT / 2 - spriteHeight / 2;
        if (drawStartY < 0) drawStartY = 0;
        int drawEndY = SCREEN_HEIGHT / 2 + spriteHeight / 2;
        if (drawEndY > SCREEN_HEIGHT) drawEndY = SCREEN_HEIGHT;
        int spriteWidth = abs(int(SCREEN_WIDTH / transformed.getY()));
        int drawStartX = spriteScreenX - spriteWidth / 2;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteScreenX + spriteWidth / 2;
        if (drawEndX > SCREEN_WIDTH) drawEndX = SCREEN_WIDTH;
        for (int x = drawStartX; x < drawEndX; x++) {
            int texX = int(256 * (x - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
            // todo 0.1 eller 0?
            if (transformed.getY() > 0.1 && x > 0 && x < SCREEN_WIDTH && transformed.getY() < zBuffer[x]) {
                for (int y = drawStartY; y < drawEndY; y++) {
                    int d = y * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128;
                    int texY = ((d * 64) / spriteHeight) / 256;
                    //sif (texY > 60) std::cout << texY << std::endl;
                    Uint32 c = dog[texY * 64 + texX];
                    if (c != 0x0908) {
                        Uint8 c1 = (Uint8) (c >> 8);
                        Uint8 c2 = (Uint8) (c >> 4) & 0x0f;
                        Uint8 c3 = ((Uint8) (c) << 4);
                        c3 = c3 >> 4;
                        c1 = c1 << 4;
                        c2 = c2 << 4;
                        c3 = c3 << 4;
                        c1 -= c1 * transformed.getY() / 31;
                        c2 -= c2 * transformed.getY() / 31;
                        c3 -= c3 * transformed.getY() / 31;
                        int r = abs((x - SCREEN_WIDTH / 2)) + abs((y + yOffset - SCREEN_HEIGHT / 2)) + 25;
                        c1 = ((int) c1) * 50 / r;
                        c2 = ((int) c2) * 50 / r;
                        c3 = ((int) c3) * 50 / r;
                        pixels[(y + yOffset + spriteHeight / 2) * SCREEN_WIDTH + x] = (((Uint32) c3) + (((Uint32) c2) << 8) + (((Uint32) c1) << 16) + (((Uint32) 255) << 24)); // todo krashar här
                    }
                }
            }
        }
    }
}

void update_screen() {
    SDL_UnlockTexture(texture);
    clear_screen();
    //SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, NULL, &textureRenderSize);
    SDL_RenderPresent( renderer );
}

void clear_screen() {
    SDL_SetRenderDrawColor( renderer, 10, 20, 50, 0xFF );
    SDL_RenderClear( renderer );
}
