//
//  Player.cpp
//  Basic Platform
//
//  Created by Adrian Kothman on 11/4/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#include "Player.h"

Player::Player(){
    init();
    respawn();
    printf("Level: %i\n", currentLvl->getLvl());

#ifdef DEBUG
#endif
    
}


void Player::init(){
    x = 10;
    y = 10;
    aX = 40.0 / FPS;
    aY = 15.0 / FPS;
    vXMax = 250.0 / FPS;
    friction = .96;
    sizeX = 10;
    sizeY = 20;
    hearts = 5;
    vX = 0.0;
    vY = 10.0 / FPS;
    nextLevelCountdown = 0.0;
    jumping = falling = goal = disableControls = false; // can jump 3x50
    currentLvl = new LevelOne();
}



void Player::drawEverything(){
    drawLevel();
    al_draw_filled_rectangle(drawbox->x1, drawbox->y1, drawbox->x2, drawbox->y2, al_map_rgb(200, 200, 200));
}

void Player::handleMovement(bool up, bool down, bool left, bool right){
    
    if (!disableControls) {
        //Handling keys
        if (up) {
            if (floorCollision()){
                vY = -6.0;
            }
        }
        if (left||right) {
            if(left){
                if( abs(vX - aX) < vXMax )
                    vX -= aX;
            }
            if(right){
                if( abs(vX + aX) < vXMax )
                    vX += aX;
            }
        } else {
            vX = friction * vX;
        }
    } else {
        vX = friction * vX;
        nextLevelCountdown += 1.0 / FPS;
    }

    if(!floorCollision())
        vY+=aY;
    dx = (int)vX;
    dy = (int)vY;
    
    //Updating location
    if ( dx < 0){ // left
        for (int i = 0; i > dx; i--){
            if (leftCollision()) {
                vX = 0;
            } else {
                xOffset++;
                hitbox->x1--;
                hitbox->x2--;
            }
        }
    } else if (dx > 0) { // right
        for (int i = 0; i < dx; i++){
            if(rightCollision()){
                vX = 0;
            } else {
                xOffset--;
                hitbox->x1++;
                hitbox->x2++;
            }
        }
    }
    
    if (dy < 0) { //ie jumping
        jumping = true;
        for (int i = 0; i > dy; i--) {
            if(topCollision()){
                jumping = false;
                vY = 0;
            } else {
                //printf("Should be jumping....");
                drawbox->y1-=1;
                drawbox->y2-=1;
                hitbox->y1-=1;
                hitbox->y2-=1;
            }
        }
    } else if (dy > 0) { //falling
        //printf("vY: %f\n", vY);
        jumping = false;
        falling = true;
        for (int i = 0; i < dy; i++){
            if (floorCollision()) {
                falling = false;
                vY = 0;
            } else {
                drawbox->y1+=1;
                drawbox->y2+=1;
                hitbox->y1+=1;
                hitbox->y2+=1;
            }
        }
    }

    
    if (offScreen())
        death();
    
    if (goalCollision()){
        disableControls = true;
        al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    if (nextLevelCountdown>=1.8){

        switch (currentLvl->getLvl()) {
            case 1:
                //
                setLevel(new LevelTwo());
                al_rest(1.5);
                respawn();
                break;
            case 2:
                //
                setLevel(new LevelThree());
                al_rest(1.5);
                respawn();
                break;
            case 3:
                //
                break;
                
            default:
                printf("Uh oh... Something went wrong...\n");
                break;
        }
    }

}

int Player::getLvl(){
    return currentLvl->getLvl();
}

#ifdef DEBUG

void Player::addRect(Rectangle r){
    currentLvl->addFloor(r);
}

void Player::removeLastRect(){
    currentLvl->removeLastRect();
}

void Player::drawGraph(ALLEGRO_FONT *f){
    for (int i = -100; i < 5000; i+=50) {
        if(i >= xOffset - WINDOW_WIDTH/2 || i <= xOffset + WINDOW_WIDTH){
            al_draw_line(i + xOffset, MENU_HEIGHT, i + xOffset, WINDOW_HEIGHT, al_map_rgb(255, 255, 255), 2);
            char str[20];
            sprintf(str, "(%i)", i);
            al_draw_text(f, al_map_rgb(255, 255, 255), i + 4 + xOffset, MENU_HEIGHT + 4, 0, str);
        }
    }
    for (int i = MENU_HEIGHT + 50; i<=WINDOW_HEIGHT; i+=50){
        al_draw_line(0, i, WINDOW_WIDTH, i, al_map_rgb(255, 255, 255), 2);
            char str[20];
            sprintf(str, "(%i)", i);
            al_draw_text(f, al_map_rgb(255, 255, 255), 4, i - 22, 0, str);
    }
}

void Player::returnFloors(){
    currentLvl->printFloors();
}

void Player::printStats(){
    printf("vX: %f vY: %f aX: %f aY: %f dX: %i dY: %i\n", vX, vY, aX, aY, dx, dy);
}

#endif



//Privates

void Player::setLevel(Level *l){
    score+=1000;
    currentLvl = l;
}
bool Player::collision(){
    if(currentLvl->collision(*hitbox))
        return true;
    return false;
}

bool Player::topCollision(){
    if(currentLvl->topCollision(*hitbox))
        return true;
    return false;
}
bool Player::floorCollision(){
    if(currentLvl->bottomCollision(*hitbox))
        return true;
    return false;
}
bool Player::leftCollision(){
    if(currentLvl->leftCollision(*hitbox))
        return true;
    return false;
}
bool Player::rightCollision(){
    if(currentLvl->rightCollision(*hitbox))
        return true;
    return false;
}

bool Player::goalCollision(){
    if(currentLvl->goalCollision(*hitbox))
        return true;
    else return false;
}

void Player::drawLevel(){
    currentLvl->draw(xOffset);
}

bool Player::offScreen(){
    if (hitbox->y2>=WINDOW_HEIGHT)
        return true;
    return false;
}

void Player::death(){
    hearts--;
    score-=100;
    if ( hearts <= 0) {
        youLose = true;
    }
    respawn();
    
}

void Player::respawn(){
    xOffset = WINDOW_WIDTH/2;
    vX = 0;
    vY = 0;
    disableControls = false;
    nextLevelCountdown = 0;
    
    hitbox = new Rectangle(0 - sizeX, WINDOW_HEIGHT/2 - sizeY, 0 + sizeX, WINDOW_HEIGHT/2 + sizeY);
    
    //Drawbox x should be const
    drawbox = new Rectangle(WINDOW_WIDTH/2 - sizeX, WINDOW_HEIGHT/2 - sizeY, WINDOW_WIDTH/2 + sizeX, WINDOW_HEIGHT/2 + sizeY);
    
}





