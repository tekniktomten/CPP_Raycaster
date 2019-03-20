#include <iostream>
#include "Raycaster.hpp"
#include "global.hpp"

Raycaster::Raycaster(Uint32 *pixelArray, Player *player) {
    
}
void Raycaster::raycast(Player *player, int worldMap[96][32], int wallHeightMultiplier, bool renderFloor, bool rederCeiling) {
    pos = player -> pos;
    dir = player -> dir;
    cam = player -> cam;
    wallH = wallHeightMultiplier;
    int textureWidth = 128;
    int textureHeight = 128 * wallH;
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        
        box = Vector2d((int) pos.getX(), (int) pos.getY());
        
        rayDir = (cam * (2.0 * i / SCREEN_WIDTH - 1.0)) + dir;
        
        sideToNextSide = Vector2d(abs(1.0 / rayDir.getX()), abs(1.0 / rayDir.getY()));
        
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
            else if (orthDistance > viewDistance) {
                tooFar = true;
                break;
            }
        }
        
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
        
        int actualWallBottom = wallBottom;
        
        if (wallTop < 0) wallTop = 0;
        if (wallBottom > SCREEN_HEIGHT) wallBottom = SCREEN_HEIGHT;
        
        /*if (textureIndex == 33) {
         // draws untextured wall
         if (vertical_side) SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
         else SDL_SetRenderDrawColor(renderer, red / 2, green / 2, blue / 2, 255);
         SDL_RenderDrawLine(renderer, i, wallTop, i, wallBottom);
         } else {*/
        
        if (true) { // todo why?
            
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
                    
                    c1 -= c1 * orthDistance / (viewDistance + 1);
                    c2 -= c2 * orthDistance / (viewDistance + 1);
                    c3 -= c3 * orthDistance / (viewDistance + 1);
                    
                    int r = sqrt((float)(i - SCREEN_WIDTH / 2) * (i - SCREEN_WIDTH / 2) + (y + yOffset - SCREEN_HEIGHT / 2) * (y + yOffset - SCREEN_HEIGHT / 2));
                    //int r = abs((i - SCREEN_WIDTH / 2)) + abs((y + yOffset - SCREEN_HEIGHT / 2));
                    if (r < 30) r = 30;
                    c1 = ((int) c1) * 30 / r;
                    c2 = ((int) c2) * 30 / r;
                    c3 = ((int) c3) * 30 / r;
                    
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
            
            tooFar = false;
            for (int y = SCREEN_HEIGHT - yOffset; y > wallBottom - yOffset; y--) {
                if ((y + yOffset) * SCREEN_WIDTH + i > 0 && (y + yOffset) * SCREEN_WIDTH + i < SCREEN_HEIGHT * SCREEN_WIDTH) { // todo prevents crashes
                    double currentDistance = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
                    if (currentDistance > viewDistance) tooFar = true;
                    if (!tooFar) {
                        double weight = (currentDistance * wallH) / (orthDistance);
                        Vector2d currentFloor = Vector2d(weight * floorWall.getX() + (1.0 - weight) * pos.getX(), weight * floorWall.getY() + (1.0 - weight) * pos.getY());
                        if (worldMap[(int) currentFloor.getY()][(int) currentFloor.getX()] < 1) {
                            Vector2d floorTexture = Vector2d((int) (currentFloor.getX() * textureWidth / 2) % textureWidth, (int) (currentFloor.getY() * textureHeight / 4) % textureHeight);
                            Uint16 color_ceiling = ice2[int(textureWidth * floorTexture.getY() + floorTexture.getX())];
                            Uint8 c1_c = (Uint8) (color_ceiling >> 8);
                            Uint8 c2_c = (Uint8) (color_ceiling >> 4) & 0x0f;
                            Uint8 c3_c = ((Uint8) (color_ceiling) << 4);
                            c3_c = c3_c >> 4; // todo
                            c1_c = c1_c << 4;
                            c2_c = c2_c << 4;
                            c3_c = c3_c << 4;
                            
                            c1_c -= c1_c * currentDistance / (viewDistance + 1);
                            c2_c -= c2_c * currentDistance / (viewDistance + 1);
                            c3_c -= c3_c * currentDistance / (viewDistance + 1);
                            
                            //int r = sqrt((float)(i - SCREEN_WIDTH / 2) * (i - SCREEN_WIDTH / 2) + (y + yOffset - SCREEN_HEIGHT / 2) * (y + yOffset - SCREEN_HEIGHT / 2));
                            int r = abs((i - SCREEN_WIDTH / 2)) + abs((y + yOffset - SCREEN_HEIGHT / 2));
                            if (r < 30) r = 30;
                            c1_c = ((int) c1_c) * 30 / r;
                            c2_c = ((int) c2_c) * 30 / r;
                            c3_c = ((int) c3_c) * 30 / r;
                            pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) c3_c) + (((Uint32) c2_c) << 8) + (((Uint32) c1_c) << 16) + (((Uint32) 255) << 24));
                        } else pixels[(y + yOffset) * SCREEN_WIDTH + i] = 4278190080; // black
                    }
                }
            }
            
            /*for (int y = wallBottom - yOffset; y < SCREEN_HEIGHT - yOffset; y++) {
                c1_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10);
                c2_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10);
                c3_c = (((SCREEN_HEIGHT) - (2 * y)) / - 10) * 1.4;
                pixels[(y + yOffset) * SCREEN_WIDTH + i] = (((Uint32) c3_c) + (((Uint32) c2_c) << 8) + (((Uint32) c1_c) << 16) + (((Uint32) 255) << 24));
            }*/
        }
        zBuffer[i] = orthDistance;
    }
}
