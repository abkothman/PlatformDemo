//
//  Goal.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/13/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef Basic_Platform_Goal_h
#define Basic_Platform_Goal_h

#include "Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

class Goal: public Rectangle{
  public:
    Goal(int x1, int y1) : Rectangle(x1, y1, x1 + 150, y1 + 20){
        grey = al_map_rgb(150, 150, 150);
        white = al_map_rgb(255, 255, 255);
        
        // init spine arrays
        
        //x: 600 + 125 base y: 450 base
        pt1[0] = x1 + 125; pt1[1] = y1 - 50; pt1[2] = x1 + 125 - 6; pt1[3] = y1 - 35; pt1[4] = x1 + 125 + 16; pt1[5] = y1 - 13; pt1[6] = x1 + 125; pt1[7] = y1;
        pt2[0] = x1 + 125 + 12; pt2[1] = y1 - 55; pt2[2] = x1 + 125 + 7; pt2[3] = y1 - 35; pt2[4] = x1 + 125 + 16; pt2[5] = y1 - 13; pt2[6] = x1 + 125; pt2[7] = y1;
        
        ///////
        
    };
    void draw(int xOffset){
        for (int x = 0; x < 150; x+=10){
            for (int y = 0; y < 20; y+=10){
                if((x + y)%20 == 0)
                    al_draw_filled_rectangle(x1 + x + xOffset, y1 + y, x1 + x + 10 + xOffset, y1 + y + 10, al_map_rgb(255, 255, 255));
                else
                    al_draw_filled_rectangle(x1 + x + xOffset, y1 + y, x1 + x + 10 + xOffset, y1 + y + 10, al_map_rgb(150, 150, 150));
            }
        }
        float f1[8] = {pt1[0] + xOffset, pt1[1], pt1[2] + xOffset, pt1[3], pt1[4] + xOffset, pt1[5], pt1[6] + xOffset, pt1[7]};
        float f2[8] = {pt2[0] + xOffset, pt2[1], pt2[2] + xOffset, pt2[3], pt2[4] + xOffset, pt2[5], pt2[6] + xOffset, pt2[7]};
        al_draw_spline(f1, al_map_rgb(200, 255, 200), 2);
        al_draw_spline(f2, al_map_rgb(210, 235, 220), 2);
        al_draw_filled_ellipse(x1 + 125 + xOffset, y1 - 50 - 17, 12, 18, al_map_rgb_f(255, 0, 0));
        al_draw_filled_ellipse(x1 + 125 + 12 + xOffset, y1 - 55 - 17, 11, 17, al_map_rgb_f(255, 255, 0));
    };
  private:
    ALLEGRO_COLOR grey, white, current;
    float pt1[8] = {600, 400, 594, 415, 616, 437, 600, 450};
    float pt2[8] = {612, 395, 607, 415, 616, 437, 600, 450};
};

#endif
