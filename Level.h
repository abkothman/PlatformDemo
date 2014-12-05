//
//  Level.h
//  Basic Platform
//
//  Created by Adrian Kothman on 11/5/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#ifndef __Basic_Platform__Level__
#define __Basic_Platform__Level__

#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "Globals.h"
#include "Goal.h"

class Level {
  public:
    Level(){};
    int getLvl(){
        return num;
    }
    bool collision(Rectangle player){
        for (int x = 0; x<floors.size(); x++) {
            if(floors.at(x).collision(player))
                return true;
        }
        return false;
    }
    bool topCollision(Rectangle player){
        for (int x = 0; x<floors.size(); x++) {
            if(floors.at(x).topCollision(player)){
                return true;
            }
        }
        return false;
    }
    bool bottomCollision(Rectangle player){
        for (int x = 0; x<floors.size(); x++) {
            if(floors.at(x).bottomCollision(player)){
                return true;
            }
        }
        return false;
    };
    bool rightCollision(Rectangle player){
        for (int x = 0; x<floors.size(); x++) {
            if(floors.at(x).rightCollision(player)){
                return true;
            }
        }
        return false;
    };
    bool leftCollision(Rectangle player){
        for (int x = 0; x<floors.size(); x++) {
            if(floors.at(x).leftCollision(player)){
                return true;
            }
        }
        return false;
    };
    bool goalCollision(Rectangle player){
        if(goal->bottomCollision(player))
            return true;
        return false;
    }
    void draw(int xOffset){
        for (int x = 0; x<floors.size(); x++){
            floors.at(x).draw(xOffset);
        }
        for (int x = 0; x<traps.size(); x++){
            traps.at(x).draw(xOffset);
        }
        goal->draw(xOffset);
    };
    void addFloor(Rectangle f){
        floors.push_back(f);
    };
    void setLvl(int x){
        num = x;
    };
    void setGoal(Goal *g){
        goal = g;
    };
    void printFloors(){
        printf("\n");
        for (int x = 0; x<floors.size(); x++) {
            floors.at(x).println();
        }
        printf("\n");
    }
    
    
#ifdef DEBUG
    void removeLastRect(){
        floors.pop_back();
    };
#endif
    
  private:
    Goal *goal;
    std::vector<Rectangle> traps;
    std::vector<Rectangle> floors;
    int num;
};

#endif /* defined(__Basic_Platform__Level__) */
