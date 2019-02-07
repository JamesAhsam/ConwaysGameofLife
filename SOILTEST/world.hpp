//
//  world.hpp
//  SOILTEST
//
//  Created by James Ahsam on 06/02/2019.
//  Copyright © 2019 James Ahsam. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include "main.h"
#include <vector>

struct Node{
    int x;
    int y;
    bool on;
    
    bool tempState; //Temporary state change variable. Any change gets pushed onto this and not onto the 'on' variable. This is to allow for the worlds whole state to be considered and achieve the correct behavoir
    
    Node(int x, int y): x(x), y(y), on(false), tempState(false){};
    Node(): x(-1), y(-1), on(false), tempState(false){};
    
    void turnOn(){this->tempState = true;};
    void turnOff(){this->tempState = false;};
    
    //This affects any changes from the temporary state.
    void pushChanges(){
        this->on = tempState;
    }
    
    /*
     * The order of the array provided
     *
     * 0 1 2
     * 3   4
     * 5 6 7
     *
     * This isn't needed but could be valuable at some point.
     */
    void update(bool around[]){
        //Count amount of neighbours
        int neighbors = 0;
        for(int i=0; i < 8; i++){
            if(around[i])
                neighbors++;
        }
        
        //implement ruleset based on the amount of neighbors
        if(neighbors < 2 && this->on)
            turnOff();
        if(neighbors >= 4 && this->on)
            turnOff();
        
        if(neighbors == 3 && !this->on)
            turnOn();
    };
};

class World {
    int x, y; //Map X and Y position
    
    int width, height; //Map Tile width and height
    
    int black, white; //Texture IDs of the black and white tiles
    
private:
    std::vector<std::vector<Node*>> nodes; //List of all nodes. A vector to allow us to add or change the node map in the future.
    
    int cx = 0, cy = 0; //Cursor X and Y
    const int tileSize = 8; //Pixel width of the tile
    
    int blackCursor, whiteCursor; //Texture IDs of the black and white cursor
    int waitFrames = 60; //The amount of frames until the simulation ticks once more
    
public:
    World(int width, int height);
    
    void render();
    void update(int value);
    
    void setPosition(int x, int y){this->x = x; this->y = y;}
    void addPosition(int x, int y){this->x += x; this->y += y;}
    int getBoundWidth(){return width*tileSize;}
    int getBoundHeight(){return width*tileSize;}
    int getCursorX(){return cx;}
    int getCursorY(){return cy;}
    
    int getWaitFrames(){return waitFrames;}
    
    void increaseSpeed(){(waitFrames < 600) ? waitFrames *= 2 : waitFrames = 600;}
    void decreaseSpeed(){(waitFrames > 10) ? waitFrames /= 2 : waitFrames = 10;}
    
    void moveCursor(int x, int y){this->cx += x; this->cy += y;}
    
    bool getNodeActive(int x, int y);
    
    void select();
};


#endif /* world_hpp */
