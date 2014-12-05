//
//  Rectangle.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/5/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef __Basic_Platform__Rectangle__
#define __Basic_Platform__Rectangle__

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"

class Rectangle {
  public:
    int x1, y1, x2, y2;
    bool drawable;
    
    Rectangle(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
        drawable = true;
    };
    bool collision(Rectangle r){
        if (drawable){
            if (pointCollision(r.x1, r.y1)||
                pointCollision(r.x1, r.y2)||
                pointCollision(r.x2, r.y1)||
                pointCollision(r.x2, r.y2)) {
                return true;
            }
        }
        return false;
    };
    bool topCollision(Rectangle r){
        if (topPointCollision(r.x1, r.y1)||
            topPointCollision(r.x2, r.y1))
            return true;
        
        return false;
    };
    bool bottomCollision(Rectangle r){
       if (bottomPointCollision(r.x1, r.y2)||
           bottomPointCollision(r.x2, r.y2))
           return true;
        return false;
    };
    bool leftCollision(Rectangle r){
        for (int y = r.y1; y <= r.y2; y++){
            if(leftPointCollision(r.x1, y))
                return true;
        }
        return false;
    };
    bool rightCollision(Rectangle r){
        for (int y = r.y1; y <= r.y2; y++) {
            if(rightPointCollision(r.x2, y))
                return true;
        }
        return false;
    };
    void draw(int xOffset){
        if(drawable)
            al_draw_filled_rectangle(x1 + xOffset, y1, x2 + xOffset, y2, al_map_rgb(100, 0, 100));
        
    };
    void println(){
        printf("addFloor(Rectangle(%i, %i, %i, %i + platformHeight));\n", x1, y1, x2, y2 - 20);
    };
    
  private:
    bool pointCollision(int x, int y){
        if(x >=x1 && x <= x2 &&
           y >=y1 && y <= y2){
            return true;
        }
        return false;
    };
    bool bottomPointCollision(int x, int y){
        if(x >= x1 && x <= x2 &&
           y + 1 >= y1 && y <= y2){
            return true;
        }
        return false;
    };
    bool topPointCollision(int x, int y){
        if((x >= x1 && x <= x2 &&
           y >= y1 && y - 1 <= y2)|| // OR if the player bumps the ceilling
           y <= MENU_HEIGHT + MENU_THICKNESS)
            return true;
        return false;
    };
    bool leftPointCollision(int x, int y){
        if(x >= x1 && x - 1 <= x2 &&
           y >= y1 && y <= y2)
            return true;
        return false;
    };
    bool rightPointCollision(int x, int y){
        if(x + 1 >= x1 && x <= x2 &&
           y >= y1 && y <= y2)
            return true;
        return false;
    };
};

#endif /* defined(__Basic_Platform__Rectangle__) */
