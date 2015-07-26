//
//  CoreType.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__CoreType__
#define __DollEngine__CoreType__

#include "CoreMacros.h"


DE_BEGIN

enum {
    VERTEX_ATTRIB_FLAG_NONE       = 0,
    
    VERTEX_ATTRIB_FLAG_POSITION   = 1 << 0,
    VERTEX_ATTRIB_FLAG_COLOR      = 1 << 1,
    VERTEX_ATTRIB_FLAG_TEX_COORD = 1 << 2,
    
    VERTEX_ATTRIB_FLAG_POS_COLOR_TEX = (VERTEX_ATTRIB_FLAG_POSITION | VERTEX_ATTRIB_FLAG_COLOR | VERTEX_ATTRIB_FLAG_TEX_COORD),
};

enum PROGRAM_ATTRIBUTE
{
    PROGRAM_VERTEX_ATTRIBUTE=0,
    PROGRAM_COLOR_ATTRIBUTE,
    PROGRAM_TEXCOORD_ATTRIBUTE,
    PROGRAM_OPACITY_ATTRIBUTE,
    PROGRAM_TEXTURE_ATTRIBUTE,
    PROGRAM_FBO_ATTRIBUTE,
    PROGRAM_MATRIX_ATTRIBUTE,
};

enum PROGRAM_TYPE
{
    NORMAL_PROGRAM = 0,//正常模式
    CROSSFADE_PROGRAM = 1,//trans中使用的crossfade模式
};

class Rect
{
public:
    Rect():x(0),y(0),width(0),height(0){}
    Rect(float x,float y,float w,float h);
    void set(float x,float y,float w,float h);
    static const Rect& Zero();
    
    
    float x;
    float y;
    float width;
    float height;
};

class Size
{
public:
    Size():width(0),height(0){}
    Size(float w,float h);
    void set(float w,float h);
    static const Size& Zero();
    
    float width;
    float height;
};

class Color
{
public:
    Color();
    Color(const Color& v);
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

class GradientColor:public Color
{
public:
    GradientColor();
    GradientColor(const Color& start, const Color& e);
    Color end;
    bool horizontal;
};

class FontData
{
public:
    FontData()
    :xMin(0),xMax(0),yMin(0),yMax(0),advance(0),bearingX(0),bearingY(0),outlineSize(0){}
    int xMin;//左右宽高与orgin的偏移量
    int xMax;
    int yMin;
    int yMax;
    
    int advance;//字间距
    
    int bearingX;//图片应该的orgin偏移量
    int bearingY;
    
    float outlineSize;
};

DE_END


#endif /* defined(__DollEngine__CoreType__) */
