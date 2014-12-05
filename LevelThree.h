//
//  LevelThree.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/14/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef Basic_Platform_LevelThree_h
#define Basic_Platform_LevelThree_h

#include "Level.h"

class LevelThree: public Level {
public:
    LevelThree() : Level(){
        
        addFloor(Rectangle(-1000, 0 + MENU_HEIGHT + MENU_THICKNESS, -100, WINDOW_HEIGHT));
        addFloor(Rectangle(-100, 400, 310, 400 + platformHeight));
        addFloor(Rectangle(2850, 450, 3000, 480 + platformHeight));
        addFloor(Rectangle(350, 350, 400, 350 + platformHeight));
        addFloor(Rectangle(450, 300, 500, 300 + platformHeight));
        addFloor(Rectangle(600, 400, 650, 400 + platformHeight));
        addFloor(Rectangle(750, 350, 800, 350 + platformHeight));
        addFloor(Rectangle(900, 300, 950, 300 + platformHeight));
        addFloor(Rectangle(1100, 450, 1150, 450 + platformHeight));
        addFloor(Rectangle(1150, 400, 1200, 400 + platformHeight));
        addFloor(Rectangle(2850, 450, 3000, 480 + platformHeight));
        addFloor(Rectangle(1200, 350, 1250, 350 + platformHeight));
        addFloor(Rectangle(1225, 300, 1250, 300 + platformHeight));
        addFloor(Rectangle(1100, 250, 1137, 250 + platformHeight));
        addFloor(Rectangle(1250, 200, 1400, 200 + platformHeight));
        
        setGoal(new Goal(2850, 450));
        addFloor(Rectangle(2850, 450, 3000, 500));
        
        printf("Added floor\n");
        printFloors();
        setLvl(3);
    };
private:
    int platformHeight = 18;
};


#endif
