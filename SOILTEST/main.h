//
//  main.h
//  SOILTEST
//
//  Created by James Ahsam on 06/02/2019.
//  Copyright © 2019 James Ahsam. All rights reserved.
//

#ifndef main_h
#define main_h

//This is to allow for me to work on code that was originally made in VS on a windows machine as I have two devices - Windows Desktop and Mac Laptop.
#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE  1


#include <iostream>

#include <string.h>
#include <cmath>
#include <math.h>

#include <sstream>

#include <OpenGL/gl.h> //OSx libs
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <SOIL/SOIL.h>

#include "renderer.hpp"
#include "world.hpp"

extern int font;

extern int mousex;
extern int mousey;
extern bool leftclick;
extern bool leftclick_flag;
extern bool rightclick;
extern bool rightclick_flag;

extern bool paused;

extern char homeDirectory[100];

extern int windowx;
extern int windowy;
extern float screenmultx;
extern float screenmulty;


#endif /* main_h */
