#ifndef Player_hpp
#define Player_hpp

#include "Vector2d.hpp"

struct Player {
    Player();
    Vector2d pos;
    Vector2d dir;
    Vector2d cam;
    double movementSpeed;
    double actualSpeed;
    bool forward;
    bool backward;
    bool right;
    bool left;
    bool sprint;
};

#endif /* Player_hpp */
