#ifndef Raycaster_hpp
#define Raycaster_hpp

#include <SDL2/SDL.h>
#include "Vector2d.hpp"
#include "Player.hpp"

class Raycaster {
private:
    int textureWidth;
    int textureHeight;
    double orthDistance;
    int hit;
    bool vertical_side;
    int wallHeight;
    int wallTop;
    int wallBottom;
    int maxYOffset;
    int wallH;
    Vector2d pos;
    Vector2d dir;
    Vector2d cam;
    Vector2d box; // Should always contain integers
    Vector2d rayDir;
    Vector2d rayDistance;
    Vector2d sideToNextSide;
    Vector2d step;
    Vector2d floorWall;
public:
    Raycaster(Uint32 *pixelArray, Player *player);
    void raycast(Player *player, int map[96][32], int wallHeightMultiplier, bool floor, bool ceiling);
};

#endif /* Raycaster_hpp */
