//
//  main.cpp
//  Game of Life BBC
//
//  Created by James Ahsam on 06/02/2019.
//  Copyright © 2019 James Ahsam. All rights reserved.
//

#include "main.h"

int mousex = 0;
int mousey = 0;
int font;

bool leftclick;
bool leftclick_flag;
bool rightclick;
bool rightclick_flag;

bool paused = true;

int fps = 60;
float fpsMult = 60.0f / (float)fps;
int framerate = 1000 / fps;

int windowx = 640; //our screen size
int windowy = 480;
float screenmultx = 1.0; //the pixel to pixel value. e.g. 2 world mean for every 1 pixel in the view it occupys 2 pixels on the display.
float screenmulty = 1.0;

World* world;

//Renderes the pause menu
void renderPauseMenu(){
    if(!paused) //so as to not display if paused
        return;
    
    drawtext(font, "Paused", 0, 0, 16, 16);
    drawtext(font, "  WASD - Move Cursor", 5, 25, 12, 12);
    drawtext(font, "ARROWS - Move Map", 5, 40, 12, 12);
    drawtext(font, "     F - Toggle", 5, 55, 12, 12);
    drawtext(font, " SPACE - Pause", 5, 70, 12, 12);
    drawtext(font, "Q or E - Change Speed", 5, 85, 12, 12);
    
}

//This long method is to build a long string with any datat we wan't at the bottom.
void renderInterface(){
    char worldData[100] = "(";
    
    char worldX[16];
    sprintf(worldX, "%d", world->getCursorX());
    
    char worldY[16];
    sprintf(worldY, "%d", world->getCursorY());
    
    strcat(worldData, worldX);
    strcat(worldData, ", ");
    strcat(worldData, worldY);
    strcat(worldData, ")");
    
    if(world->getNodeActive(world->getCursorX(), world->getCursorY()))
        strcat(worldData, " on.");
    else
        strcat(worldData, " off.");
    
    strcat(worldData, " SPEED: ");
    
    char waitFrames[16];
    sprintf(waitFrames, "%f", ((float)world->getWaitFrames())/((float)fps));
    
    strcat(worldData, waitFrames);
    strcat(worldData, " seconds.");
    
    drawtext_centre(font, worldData, windowx/2, windowy-16, 12, 12);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    enable2d((int)windowx, (int)windowy); // this initialised the OpenGL model view to work as expected in 2d.
    
    //initialise using forward rendering. Not preferred, just works for this situation.
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND); //Our opacity filter
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    
    world->render();
    
    renderPauseMenu();
    
    renderInterface();
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    glutSwapBuffers();
}

void update(int value)
{
    world->update(value);
    
    glutTimerFunc(framerate, update, 0);
    
    draw();
    
}

//This handles mouse input - is not used during this demo
void basic_mouse_func(int button, int state, int x, int y){
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(leftclick_flag == false && leftclick == true)
            leftclick_flag = true;
        else
            leftclick_flag = false;
        
        leftclick = true;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        leftclick_flag = false;
        leftclick = false;
    }
    
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if(rightclick_flag == false && rightclick == true)
            rightclick_flag = true;
        else
            rightclick_flag = false;
        
        rightclick = true;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        rightclick_flag = false;
        rightclick = false;
    }
}

//This is our controls
void processNormalKeys(unsigned char key, int x, int y) {
    
    if(key == 113)//Q
        world->increaseSpeed();
    
    if(key == 101)//E
        world->decreaseSpeed();
    
    if(key == 97)//A
        world->moveCursor(-1, 0);
        
    if(key == 100)//D
        world->moveCursor(1, 0);
        
    if(key == 119)//W
        world->moveCursor(0, -1);
            
    if(key == 115)//S
        world->moveCursor(0, 1);
    
    if(key == 102)//F to select
        world->select();
    
    if(key == 32)//Space
        paused = !paused;
    
    if (key == 27) //Escape
        exit(0);
}

void processSpecialKeys(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_LEFT : world->addPosition(-8, 0); break;
        case GLUT_KEY_RIGHT : world->addPosition(8, 0); break;
        case GLUT_KEY_DOWN : world->addPosition(0, 8); break;
        case GLUT_KEY_UP : world->addPosition(0, -8); break;
    }
}

void initGame(){
    //load the font texture
    font = LoadTexture("textures", "font_oswald.png");
    
    //load the world and set it to the middle of the current view
    world = new World(50, 50);
    world->setPosition(windowx/2-world->getBoundWidth()/2, windowy/2-world->getBoundHeight()/2);
}

//If you recieve deprecation errors, this is because Mac has stopped supporting OpenGL in favor of metal. See https://developer.apple.com/macos/whats-new/
int main(int argc, char** argv)
{
    
    glutInit(&argc, argv); //inits OpenGL
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Sets the display mode
    
    glutInitWindowSize(windowx, windowy); //Sets the screen size
    glutCreateWindow("Conway's Game of Life"); //Creates the window context for the current OS
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Sets the backround color
    glutDisplayFunc(draw); //defines the function we need to call everytime we want to draw
    glutTimerFunc(framerate, update, 0); //defines the function we need to call everytime we need to do logic at the given rate "framerate"
    
    glutMouseFunc(&basic_mouse_func); //The function we call when mouse input
    glutSpecialFunc(&processSpecialKeys); //The function we call when special keys are pressed e.g. The arrows
    glutKeyboardFunc(&processNormalKeys); //The function we call when nomal keyboard keys are pressed e.g. WASD
    //glutReshapeFunc(resizeWindow); //On resize function - I normally add this but felt it wasn't necessary
    
    initGame(); //initialise the game
    
    glutMainLoop(); //give opengl control
    
    return 0;
}

