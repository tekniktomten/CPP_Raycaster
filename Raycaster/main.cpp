#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "Vector2d.hpp"
#include "Bitmaps.cpp"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
    {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
    {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
    {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
    {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
    {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
    {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

bool fullscreen = false;

int textureWidth = 64;
int textureHeight = 64;

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
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    if (!success) printf( "Failed to initialize!\n" );
    return success;
}

void close() {
    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
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

void game_loop() {
    
    // TODO maybe add a screenbuffer
    
    std::vector<Uint32> texture[8];
    for (int i = 0; i < 8; i++) texture[i].resize(textureWidth * textureHeight);

    bool trapMouse = true;
    SDL_SetRelativeMouseMode(SDL_bool(trapMouse));
    
    double time = 0;
    double lastTime = 0;
    double frameTime = 0;
    int fps = 0;
    
    Vector2d pos = Vector2d(17.5, 19);
    Vector2d dir = Vector2d(0, -1);
    Vector2d cam = Vector2d(0.707, 0);
    Vector2d box = Vector2d(22, 12); // Should always contain integers
    Vector2d rayDir = Vector2d(0, 0);
    Vector2d rayDistance = Vector2d(0, 0);
    Vector2d sideToNextSide = Vector2d(0, 0);
    Vector2d step = Vector2d(0, 0);
    
    int red;
    int green;
    int blue;
    
    double orthDistance;
    int hit = false;
    bool vertical_side = false;
    int wallHeight;
    int wallTop;
    int wallBottom;
    
    double movementSpeed = 5;
    bool forward = false;
    bool backward = false;
    bool right = false;
    bool left = false;
    
    int yOffset = 0;
    int maxYOffset = SCREEN_HEIGHT * 0.25;
    
    //Main loop flag
    bool quit = false;
    
    //Event handler
    SDL_Event e;
    
    //While application is running
    while( !quit ) {
        
        clear_screen();
        
        // raycast
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
            
            //Digital Differential Analysis
            while (!hit) {
                if (rayDistance.getX() < rayDistance.getY()) {
                    rayDistance += Vector2d(sideToNextSide.getX(), 0);
                    box += Vector2d(step.getX(), 0);
                    vertical_side = true;
                } else {
                    rayDistance += Vector2d(0, sideToNextSide.getY());
                    box += Vector2d(0, step.getY());
                    vertical_side = false;
                }
                if (worldMap[(int) box.getY()][(int) box.getX()] > 0) {
                    hit = worldMap[(int) box.getY()][(int) box.getX()];
                }
            }
            
            if (vertical_side) {
                orthDistance = (box.getX() - pos.getX() + (1.0 - step.getX()) / 2.0) / rayDir.getX();
            } else {
                orthDistance = (box.getY() - pos.getY() + (1.0 - step.getY()) / 2.0) / rayDir.getY();
            }
            
            wallHeight = (int) (SCREEN_HEIGHT / orthDistance);
            wallTop = (SCREEN_HEIGHT - wallHeight) / 2.0;
            //if (wallTop < 0) wallTop = 0;
            wallBottom = (SCREEN_HEIGHT + wallHeight) / 2.0;
            //if (wallBottom > SCREEN_HEIGHT) wallBottom = SCREEN_HEIGHT;
            
            int textureIndex = hit - 1;
            
            double wallX; // where the wall was hit
            if (vertical_side) wallX = pos.getY() + rayDir.getY() * orthDistance;
            else wallX = pos.getX() + rayDir.getX() * orthDistance;
            wallX -= floor(wallX);
            
            int textureX = (int) (wallX * (double) textureWidth); // x cordinate in texture domain
            if ((vertical_side && rayDir.getX() > 0) or (!vertical_side && rayDir.getY() < 0)) textureX = textureWidth - textureX - 1;
            
            
            switch (hit) {
                case 1: {
                    red = 0;
                    green = 42;
                    blue = 42;
                    break;
                }
                case 2: {
                    red = 42;
                    green = 42;
                    blue = 42;
                    break;
                }
                case 3: {
                    red = 200;
                    green = 0;
                    blue = 200;
                    break;
                }
                case 4: {
                    red = 200;
                    green = 200;
                    blue = 0;
                    break;
                }
                default: {
                    red = 100;
                    green = 10;
                    blue = 100;
                    break;
                }
            }
            
            if (!vertical_side) {
                red = red / 2;
                green = green / 2;
                blue = blue / 2;
            }
            
            wallTop += yOffset;
            wallBottom += yOffset;
            
            if (wallTop < 0) wallTop = 0;
            if (wallBottom > SCREEN_HEIGHT) wallBottom = SCREEN_HEIGHT;
            
            /*if (textureIndex == 33) {
                // draws untextured wall
                if (vertical_side) SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
                else SDL_SetRenderDrawColor(renderer, red / 2, green / 2, blue / 2, 255);
                SDL_RenderDrawLine(renderer, i, wallTop, i, wallBottom);
            } else {*/
            if (i % textureGranularity == 0) {
                // draws ceiling
                SDL_SetRenderDrawColor(renderer, 77, 77, 77, 255);
                SDL_RenderDrawLine(renderer, i, 0, i, wallTop);
                SDL_RenderDrawLine(renderer, i + 1, 0, i + 1, wallTop);
                //SDL_RenderDrawLine(renderer, i + 2, 0, i + 2, wallTop);
                //SDL_RenderDrawLine(renderer, i + 3, 0, i + 3, wallTop);
                
                // draws floor
                SDL_SetRenderDrawColor(renderer, 77, 77, 33, 255);
                SDL_RenderDrawLine(renderer, i, wallBottom, i, SCREEN_HEIGHT);
                SDL_RenderDrawLine(renderer, i + 1, wallBottom, i + 1, SCREEN_HEIGHT);
                //SDL_RenderDrawLine(renderer, i + 2, wallBottom, i + 2, SCREEN_HEIGHT);
                //SDL_RenderDrawLine(renderer, i + 3, wallBottom, i + 3, SCREEN_HEIGHT);
                
                for (int y = wallTop - yOffset; y < wallBottom - yOffset; y += textureGranularity) {
                    int d = y * 256 + (wallHeight - SCREEN_HEIGHT) * 128;
                    int textureY = ((d * textureHeight) / wallHeight) / 256;
                    Uint32 color = eridu223[textureHeight * textureY + textureX];
                    if(vertical_side) SDL_SetRenderDrawColor(renderer, (color & 0xff), (color >> 4), (color >> 4), 255);
                    else SDL_SetRenderDrawColor(renderer, (color & 0xff) / 2, (color >> 4) / 2, (color >> 4) / 2, 255);
                    SDL_Rect rect;
                    rect.x = i;
                    rect.y = y + yOffset;
                    rect.w = textureGranularity;
                    rect.h = textureGranularity;
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
            //}
            
            // draws wall
            //SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
            //SDL_RenderDrawLine(renderer, i, wallTop, i, wallBottom);
            
        }
        
        lastTime = time;
        time = SDL_GetTicks();
        frameTime = (time - lastTime) / 1000.0;
        fps = (int) (1.0 / frameTime);
        std::cout << "FPS: " << fps << std::endl;
        update_screen();
        
        if (forward) {
            Vector2d newPos = pos + dir.norm() * movementSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] == 0) pos += dir.norm() * movementSpeed * frameTime;        }
        if (left) {
            Vector2d newPos = pos + dir.rotate(-3.14159 / 2).norm() * movementSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] == 0) pos += dir.rotate(-3.14159 / 2).norm() * movementSpeed * frameTime;
        }
        if (backward) {
            Vector2d newPos = pos - dir.norm() * movementSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] == 0) pos -= dir.norm() * movementSpeed * frameTime;
        }
        if (right) {
            Vector2d newPos = pos + dir.rotate(3.14159 / 2).norm() * movementSpeed * frameTime * 3;
            if (worldMap[(int) newPos.getY()][(int) newPos.getX()] == 0) pos += dir.rotate(3.14159 / 2).norm() * movementSpeed * frameTime;
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
                yOffset -= e.motion.yrel;
                if (yOffset > maxYOffset) yOffset = maxYOffset;
                else if (yOffset < -maxYOffset) yOffset = -maxYOffset;
            }
            
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                
            }
        }
    }
}

void update_screen() {
    SDL_RenderPresent( renderer );
}

void clear_screen() {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
}
