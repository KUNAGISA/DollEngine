//
//  Color.h
//  DollEngine
//
//  Created by DollStudio on 15/10/5.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Color__
#define __DollEngine__Color__

#include "CoreMacros.h"

DE_BEGIN


class Color
{
public:
    Color();
    Color(const Color& v);
    Color(GLubyte r,GLubyte g,GLubyte b);
    Color(GLubyte r,GLubyte g,GLubyte b,GLubyte a);
    Color(int r,int g,int b,int a);
    Color(uint32_t color);
    void set(GLubyte r,GLubyte g,GLubyte b);
    void set(GLubyte r,GLubyte g,GLubyte b,GLubyte a);
    void set(int r,int g,int b,int a);
    void set(uint32_t color);
    void toInt32(uint32_t& color);
    void toColorF(GLfloat* colorf);
    void multiply(const Color& v);
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

class GradientColor
{
public:
    GradientColor();
    GradientColor(const Color& start, const Color& e);
    Color start;
    Color end;
    int vector; //0无渐变,1
};


DE_END

#endif /* defined(__DollEngine__Color__) */
