//
//  LevelTwo.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/13/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef Basic_Platform_LevelTwo_h
#define Basic_Platform_LevelTwo_h

#include "Level.h"

class LevelTwo: public Level {
  public:
    LevelTwo() : Level(){
        
        addFloor(Rectangle(-1000, 0 + MENU_HEIGHT + MENU_THICKNESS, -100, WINDOW_HEIGHT));
        addFloor(Rectangle(-100, 400, 310, 400 + platformHeight));
        addFloor(Rectangle(150, 370, 250, 370 + platformHeight));
        addFloor(Rectangle(450, 400, 700, 400 + platformHeight));
        addFloor(Rectangle(850, 400, 1000, 400 + platformHeight));
        addFloor(Rectangle(1100, 400, 1200, 400 + platformHeight));
        addFloor(Rectangle(1350, 400, 1400, 400 + platformHeight));
        addFloor(Rectangle(1500, 350, 1550, 350 + platformHeight));
        addFloor(Rectangle(1600, 300, 1650, 300 + platformHeight));
        addFloor(Rectangle(1700, 250, 1750, 250 + platformHeight));
        addFloor(Rectangle(1800, 200, 1900, 200 + platformHeight));
        addFloor(Rectangle(1750, 0 + MENU_HEIGHT + MENU_THICKNESS, 1775, 150));
        addFloor(Rectangle(1900, 135, 2650, 135 + platformHeight));
        addFloor(Rectangle(1900, 65, 2600, 65 + platformHeight));
        
        setGoal(new Goal(2850, 450));
        addFloor(Rectangle(2850, 450, 3000, 500));
        
        printf("Added floor\n");
        printFloors();        
        setLvl(2);
    };
  private:
    int platformHeight = 18;
};

#endif
