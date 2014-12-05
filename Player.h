//
//  Player.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/4/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef __Basic_Platform__Player__
#define __Basic_Platform__Player__

#include <iostream>
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "Rectangle.h"
#include "Globals.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>


class Player{
  public:
    Player();
    void init();
    int getHearts(){return hearts;};
    int getScore(){return score;};
    int getLvl();
    void drawEverything();
    void handleMovement(bool up, bool down, bool left, bool right);
    bool isJumping(){return jumping;};
    void setSample(ALLEGRO_SAMPLE *s){sample = s;};
    
#ifdef DEBUG
    void addRect(Rectangle r);
    void removeLastRect();
    void drawGraph(ALLEGRO_FONT *f);
    void returnFloors();
    void printStats();
#endif
    
    
    bool youLose;

    
  private:
    int vXMax, x, y, dx, dy, sizeX, sizeY, xOffset, hearts, score;
    double aX, aY, vX, vY, friction, nextLevelCountdown;
    bool jumping, falling, goal, disableControls;
    Level *currentLvl;
    Rectangle *hitbox, *drawbox;
    ALLEGRO_SAMPLE *sample;
    bool collision();
    bool topCollision();
    bool floorCollision();
    bool leftCollision();
    bool rightCollision();
    bool goalCollision();
    bool insideFloor();
    void setLevel(Level *l);
    void drawLevel();
    bool offScreen();
    void death();
    void respawn();

    
};

#endif /* defined(__Basic_Platform__Player__) */
