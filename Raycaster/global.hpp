#ifndef global_hpp
#define global_hpp

#include <SDL2/SDL.h>
#include "Bitmaps.cpp"
#include "Player.hpp"
#include "Vector2d.hpp"
#include "Player.hpp"

//Screen dimension constants
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 280

#define mapWidth 32
#define mapHeight 96

extern Uint32 *pixels;
extern int zBuffer[];
extern int yOffset;
extern int maxYOffset;
extern int pitch;
extern int viewDistance;
extern bool createMode;
extern int createWall;
extern int (*activeMap)[mapHeight][mapWidth];
#endif /* global_hpp */
