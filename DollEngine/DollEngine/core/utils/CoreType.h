//
//  CoreType.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__CoreType__
#define __DollEngine__CoreType__

#include "Macros.h"


DE_BEGIN

class Rect
{
public:
    Rect(float x,float y,float w,float h);
    void set(float x,float y,float w,float h);
    static const Rect& Zero();
    
    
    float x;
    float y;
    float width;
    float height;
};

class Color
{
public:
    Color();
    Color(GLubyte r,GLubyte g,GLubyte b);
    Color(GLubyte r,GLubyte g,GLubyte b,GLubyte a);
    Color(uint32_t color);
    void set(GLubyte r,GLubyte g,GLubyte b);
    void set(GLubyte r,GLubyte g,GLubyte b,GLubyte a);
    void set(uint32_t color);
    void toColorF(GLfloat* colorf);
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

class GradientColor
{
public:
    
    Color begin;
    Color end;
};

DE_END


#endif /* defined(__DollEngine__CoreType__) */
