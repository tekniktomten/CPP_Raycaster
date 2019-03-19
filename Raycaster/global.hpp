#ifndef global_hpp
#define global_hpp

#include <SDL2/SDL.h>
#include "Bitmaps.cpp"
#include "Player.hpp"
#include "Vector2d.hpp"
#include "Player.hpp"

//Screen dimension constants
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 270

extern Uint32 *pixels;
extern int zBuffer[];
extern int yOffset;
extern int maxYOffset;
extern int pitch;
#endif /* global_hpp */
