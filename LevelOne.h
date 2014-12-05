//
//  LevelOne.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/6/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef __Basic_Platform__LevelOne__
#define __Basic_Platform__LevelOne__

#include "Level.h"

class LevelOne: public Level {
  public:
    LevelOne() : Level(){
        addFloor(Rectangle(-1000, 0 + MENU_HEIGHT + MENU_THICKNESS, -100, WINDOW_HEIGHT));
        addFloor(Rectangle(-100, 400, 400, 400 + platformHeight));
        addFloor(Rectangle(150, 370, 250, 370 + platformHeight));
        addFloor(Rectangle(450, 400, 750, 400 + platformHeight));
        addFloor(Rectangle(800, 400, 1000, 400 + platformHeight));
        addFloor(Rectangle(1100, 400, 1200, 400 + platformHeight));
        addFloor(Rectangle(1350, 400, 1450, 400 + platformHeight));
        addFloor(Rectangle(1450, 375, 1500, 375 + platformHeight));
        addFloor(Rectangle(1500, 350, 1550, 350 + platformHeight));
        addFloor(Rectangle(1550, 325, 1600, 325 + platformHeight));
        addFloor(Rectangle(1600, 300, 1650, 300 + platformHeight));
        addFloor(Rectangle(1650, 275, 1700, 275 + platformHeight));
        addFloor(Rectangle(1700, 250, 1750, 250 + platformHeight));
        addFloor(Rectangle(1800, 200, 1900, 200 + platformHeight));
        addFloor(Rectangle(1750, 0 + MENU_HEIGHT + MENU_THICKNESS, 1775, 150));
        addFloor(Rectangle(1900, 135, 2700, 135 + platformHeight));
        addFloor(Rectangle(1900, 65, 2700, 65 + platformHeight));
        
        setGoal(new Goal(2850, 450));
        addFloor(Rectangle(2850, 450, 3000, 500));
        
        printf("Added floor\n");
        printFloors();
        setLvl(1);
    };
  private:
    int platformHeight = 20;
};

#endif /* defined(__Basic_Platform__LevelOne__) */
