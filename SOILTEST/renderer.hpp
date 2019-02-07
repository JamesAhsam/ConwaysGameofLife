//
//  renderer.hpp
//  SOILTEST
//
//  Created by James Ahsam on 06/02/2019.
//  Copyright © 2019 James Ahsam. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <stdio.h>
#include "main.h"

extern const float pi;

extern int carriage_return;

extern float screenshiftx;
extern float screenshifty;

extern float aspectRatio;

extern float renderx;
extern float rendery;

extern int mousex_dir;
extern int mousey_dir;

int LoadTexture(char* directory, char* filename);
void enable2d(int width, int height);
std::string int2string(int x);
void xrotate(float &valy, float &valz, float rotval);
void yrotate(float &valz, float &valx, float rotval);
void zrotate(float &valx, float &valy, float rotval);
void placeimageeasy(int textureimage, float x1, float y1, float width, float height, bool smoothflag);
void placeimagetile(int textureimage, float x1, float y1, float width, float height, float tilex, float tiley, bool smoothflag);
void placeimage(int textureimage, int mask, float x1, float y1, float width, float height, bool smoothflag);
void placeimagerotatecentre(int textureimage, float x1, float y1, float width, float height, float rotation, bool smoothflag);
void placeimagerotatetile(int textureimage, float x1, float y1, float width, float height, float tilex, float tiley, float rotation, bool smoothflag);
void placeimagerotatetile(int textureimage, float x1, float y1, float width, float height, float tilex, float tiley, float tilexoffset, float tileyoffset, float rotation, bool smoothflag);
void drawtext(int font, char* textval, int xstart, int ystart, int letterwidth, int letterheight);
void drawtext(int font, char* textval, int xstart, int ystart, int letterwidth, int letterheight, float widthmult);
int getintsize(int number);
void drawtextCropped2(char* textval, int xstart, int ystart, int letterwidth, int letterheight, int linelength, int font);
void drawtextCropped(char* textval, int xstart, int ystart, int letterwidth, int letterheight, int linelength, float widthmult);
void drawtext_centre(int font, char* textval, int xstart, int ystart, int letterwidth, int letterheight);
void drawtext_centre(int font, char* textval, int xstart, int ystart, int letterwidth, int letterheight, float widthMult);
void drawQuad(int textureimage, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, bool smoothflag);
float toRadians(float degrees);
void calculateScreenShift();

#endif /* renderer_hpp */
