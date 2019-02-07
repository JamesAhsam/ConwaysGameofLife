//
//  world.cpp
//  Game of Life BBC
//
//  Created by James Ahsam on 06/02/2019.
//  Copyright © 2019 James Ahsam. All rights reserved.
//

#include "world.hpp"

World::World(int width, int height) {
    this->width = width;
    this->height = height;
    
    this->nodes = std::vector<std::vector<Node*> >(width);

    for (int x = 0; x<width; x++) {
        this->nodes[x] = std::vector<Node*>(height);
        for (int y = 0; y<height; y++) {
            this->nodes[x][y] = new Node(x, y);
        }
    }
    
    //This is where you initialise the state of the map
    this->nodes[20][20]->turnOn();
    this->nodes[20][19]->turnOn();
    this->nodes[19][20]->turnOn();
    this->nodes[21][20]->turnOn();
    this->nodes[19][21]->turnOn();
    this->nodes[21][21]->turnOn();
    this->nodes[20][22]->turnOn();
    
    //Then push the changes to the state
    for (int x = 0; x<width; x++) {
        for (int y = 0; y<height; y++) {
            this->nodes[x][y]->pushChanges();
        }
    }
    
    
    //Load the textures, if the texture is already loaded don't load it.
    if(black)
        black = LoadTexture("textures", "black.png");
    
    if(white)
        white = LoadTexture("textures", "white.png");
    
    if(blackCursor)
        blackCursor = LoadTexture("textures", "cursor_black.png");
    
    if(whiteCursor)
        whiteCursor = LoadTexture("textures", "cursor_white.png");
}

bool World::getNodeActive(int x, int y){
    if(x < 0 || x >= width || y < 0 || y >= height)
        return false;
    else
        return nodes[x][y]->on;
        
}


int framesWaited = 0;

void World::select(){
    if(cx < 0 || cx >= width || cy < 0 || cy >= height)
        return;
    
    if(this->nodes[cx][cy]->on)
        this->nodes[cx][cy]->turnOff();
    else
        this->nodes[cx][cy]->turnOn();
    
    this->nodes[cx][cy]->pushChanges();
        
}

void World::update(int value) {
    
    if(paused){
        return;
    }
    
    if(framesWaited < waitFrames){
        framesWaited++;
        return;
    }
    
    framesWaited = 0;
    
    for (int x = 0; x<width; x++) {
        for (int y = 0; y<height; y++) {
            
            bool around [8] = {getNodeActive(x-1, y-1),
                getNodeActive(x, y-1),
                getNodeActive(x+1, y-1),
                getNodeActive(x-1, y),
                getNodeActive(x+1, y),
                getNodeActive(x-1, y+1),
                getNodeActive(x, y+1),
                getNodeActive(x+1, y+1)};
            this->nodes[x][y]->update(around);
        }
    }
    
    for (int x = 0; x<width; x++) {
        for (int y = 0; y<height; y++) {
            this->nodes[x][y]->pushChanges();
        }
    }
}


void World::render() {
    for (int x = 0; x<width; x++) {
        for (int y = 0; y<height; y++) {
            int texture;
            if(nodes[x][y]->on)
                texture = white;
            else
                texture = black;
            
            placeimageeasy(texture, this->x+x*tileSize, this->y+y*tileSize, tileSize, tileSize, FALSE);
        }
    }
    
    if(paused){
        
        if(!(cx < 0 || cx >= width || cy < 0 || cy >= height)){
            int texture;
            if(nodes[cx][cy]->on)
                texture = blackCursor;
            else
                texture = whiteCursor;
            
            placeimageeasy(texture, this->x+this->cx*tileSize, this->y+this->cy*tileSize, tileSize, tileSize, FALSE);

        }
    }
}


