#include "global.hpp"

Uint32 *pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

int zBuffer[SCREEN_WIDTH];

int yOffset = 0;
int maxYOffset = SCREEN_HEIGHT * 0.4;

int pitch = SCREEN_WIDTH * sizeof(Uint32);

int viewDistance = 32;

bool createMode = false;
int createWall = 0;

int (*activeMap)[mapHeight][mapWidth] = NULL;

void flashLight(int x, int y, Uint8 *c1, Uint8 *c2, Uint8 *c3, bool fancy) {
    int r;
    if (fancy) r = sqrt((float)(x - SCREEN_WIDTH / 2) * (x - SCREEN_WIDTH / 2) + (y + yOffset - SCREEN_HEIGHT / 2) * (y + yOffset - SCREEN_HEIGHT / 2));
    else r = abs((x - SCREEN_WIDTH / 2)) + abs((y + yOffset - SCREEN_HEIGHT / 2));
    if (r < 50) r = 40;
    else if (r > 100) r = 100;
    *c1 = ((int) *c1) * 50 / r;
    *c2 = ((int) *c2) * 50 / r;
    *c3 = ((int) *c3) * 50 / r;
}
