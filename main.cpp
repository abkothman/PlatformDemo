//
//  main.cpp
//  Basic Platform
//
//  Created by Adrian Kothman on 11/4/14.
//  Copyright (c) 2014 Adrian Kothman. All rights reserved.
//

#include <iostream>
#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include "Globals.h"

void init();
void mainLoop();
void shutdown();
void drawMenu();
void abortGame(const char *);
void displayLoseScreen();
#ifdef DEBUG
void addRect();
void removeLastRect();
#endif

//Variables
Player p;
std::string scoreStr;
std::string lifeStr;
std::string lvlStr;

//Allegro Variables
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *font;
ALLEGRO_COLOR backgroundColor;
ALLEGRO_SAMPLE *sample, *yaySample;


bool done;



int main(int argc, char ** argv)
{

    // insert code here...
    
    
    init();
    
    
    mainLoop();
    shutdown();
    
    return 0;
}

void mainLoop(){
    //Main Loop Declarations
    ALLEGRO_EVENT event;
    bool up, down, left, right; up = down = left = right = false;
    bool redraw = false;
    al_start_timer(timer);
    
    while (!done) {
        
        al_wait_for_event(event_queue, &event);
        
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_W:
                    case ALLEGRO_KEY_UP:
                    case ALLEGRO_KEY_SPACE:
                        up = true;
                        break;
                    case ALLEGRO_KEY_S:
                    case ALLEGRO_KEY_DOWN:
                        down = true;
                        break;
                    case ALLEGRO_KEY_D:
                    case ALLEGRO_KEY_RIGHT:
                        right = true;
                        break;
                    case ALLEGRO_KEY_A:
                    case ALLEGRO_KEY_LEFT:
                        left = true;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                    default:
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_W:
                    case ALLEGRO_KEY_UP:
                    case ALLEGRO_KEY_SPACE:
                        up = false;
                        break;
                    case ALLEGRO_KEY_S:
                    case ALLEGRO_KEY_DOWN:
                        down = false;
                        break;
                    case ALLEGRO_KEY_D:
                    case ALLEGRO_KEY_RIGHT:
                        right = false;
                        break;
                    case ALLEGRO_KEY_A:
                    case ALLEGRO_KEY_LEFT:
                        left = false;
                        break;
#ifdef DEBUG
                    case ALLEGRO_KEY_R:
                        removeLastRect();
                        break;
                    case ALLEGRO_KEY_ENTER:
                        addRect();
                        break;
                    case ALLEGRO_KEY_G:
                        p.returnFloors();
                        p.printStats();
                        break;
#endif
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        
        
        if( redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            
            p.handleMovement(up, down, left, right);
            
            
            //Redraw the display
            al_clear_to_color(backgroundColor);
            drawMenu();
            p.drawEverything();
            
#ifdef DEBUG
            p.drawGraph(font);
#endif
            if (p.youLose) {
                done = true;
                displayLoseScreen();
            }
            
            al_flip_display();
        }
    }
    
    
    
}

void abortGame(const char *message){
    printf("%s\n", message);
    exit(EXIT_FAILURE);
};

void drawMenu(){
    ALLEGRO_COLOR white = al_map_rgb_f(255, 255, 255);
    scoreStr = "Score: " + std::to_string(p.getScore());
    lifeStr = "Lives: ";
    lvlStr = "Lvl: " + std::to_string(p.getLvl());
    for (int i = 0; i<p.getHearts(); i++) {
        lifeStr.append("X");
    }
    
    al_draw_filled_rectangle(0, 0, WINDOW_WIDTH, MENU_HEIGHT, al_map_rgb(0, 0, 0));
    al_draw_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, white, MENU_THICKNESS);
    al_draw_rectangle(0, 0, WINDOW_WIDTH, MENU_HEIGHT, white, MENU_THICKNESS);
    
    al_draw_text(font, white, 5, 5, 0, lvlStr.c_str());
    al_draw_text(font, white, 100, 5, 0, scoreStr.c_str());
    al_draw_text(font, white, 5, 20, 0, lifeStr.c_str());
}

void shutdown(){
    printf("Shutting down\n");
    if (timer)
        al_destroy_timer(timer);
    if (timer)
        al_destroy_display(display);
    if (event_queue)
        al_destroy_event_queue(event_queue);
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
    //al_destroy_display(display);
    //al_destroy_sample(sample);
    
}

void init(){
    
    //Initialize Allegro
    if(!al_init())
        abortGame("Could not initialize Allegro.");
    if(!al_install_keyboard())
        abortGame("Could not install Keyboard.");
    timer = al_create_timer(1.0/FPS);
    if(!timer)
        abortGame("Could not initialize Timer");

    
    event_queue = al_create_event_queue();
    if(!event_queue)
        abortGame("Failed to create Event Queue");
    if(!al_init_primitives_addon())
        abortGame("Failed to initialize Primitives Addon");
    al_init_font_addon();
    if(!al_init_ttf_addon())
        abortGame("Failed to initialize TTF Addon");
    font = al_load_ttf_font("Sarpanch.ttf", 12, 0);
    if(!font)
        abortGame("Failed to load Font");
    
    
    if(!al_install_audio())
        abortGame("failed to initialize audio!");
    
    if(!al_init_acodec_addon())
        abortGame("failed to initialize audio codecs!");
    
    if (!al_reserve_samples(2))
        abortGame("Failed to reserve samples");
    
    sample = al_load_sample("Departure.ogg");
    yaySample = al_load_sample("yay.ogg");
    
    if(!sample)
        abortGame("Audio not loaded...");
    if(!yaySample)
        abortGame("Audio not loaded...");
    
    p.setSample(yaySample);
    
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    if(!display)
        abortGame("Could not initialize Window");
    
    al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    backgroundColor = al_map_rgb(0, 0, 0);
    
    done = false;
}

void displayLoseScreen(){
    ALLEGRO_FONT *losingFont = al_load_ttf_font("Sarpanch.ttf", 128, 0);
    int i = 5;
    while (i>=0) {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_text(losingFont, al_map_rgb(0, 0, 0), 100, 100, 0, "YOU LOSE");
        std::string num;
        num = std::to_string(i);
        char str = num.at(0);
        al_draw_text(losingFont, al_map_rgb(0, 0, 0), WINDOW_WIDTH/2 - (128/2), 300, 0, &str);
        al_flip_display();
        al_rest(1);
        i--;
    }
}

#ifdef DEBUG

void addRect(){
    int x1, y1;
    double size;
    printf("x1: ");
    std::cin >> x1;
    printf("y1: ");
    std::cin >> y1;
    printf("size: ");
    std::cin >> size;
    size *= 50;
    
    p.addRect(Rectangle(x1, y1, x1 + ((int)size), y1 + 20));
    
    
}

void removeLastRect(){
    p.removeLastRect();
}

#endif
