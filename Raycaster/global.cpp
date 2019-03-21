#include "global.hpp"

Uint32 *pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

int zBuffer[SCREEN_WIDTH];

int yOffset = 0;
int maxYOffset = SCREEN_HEIGHT * 0.4;

int pitch = SCREEN_WIDTH * sizeof(Uint32);

int viewDistance = 20;

bool createMode = false;
int createWall = 0;

int (*activeMap)[mapHeight][mapWidth] = NULL;
