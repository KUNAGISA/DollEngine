//
//  Color.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/5.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Color.h"


DE_BEGIN

Color::Color()
:r(0xff)
,g(0xff)
,b(0xff)
,a(0xff)
{
    
}

Color::Color(const Color& v)
:r(v.r),g(v.g),b(v.b),a(v.a)
{
}

Color::Color(GLubyte r,GLubyte g,GLubyte b)
:r(r)
,g(g)
,b(b)
,a(0xff)
{
    
}

Color::Color(GLubyte r,GLubyte g,GLubyte b,GLubyte a)
:r(r)
,g(g)
,b(b)
,a(a)
{
    
}

Color::Color(int r,int g,int b,int a)
{
    set(r, g, b, a);
}

Color::Color(uint32_t color)
{
    set(color);
}

void Color::set(GLubyte r,GLubyte g,GLubyte b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::set(GLubyte r,GLubyte g,GLubyte b,GLubyte a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Color::set(int r,int g,int b,int a)
{
    if(r>255) this->r = 0xff;
    else this->r = r;
    
    if(g>255) this->g = 0xff;
    else this->g = g;
    
    if(b>255) this->b = 0xff;
    else this->b = b;
    
    if(a>255) this->a = 0xff;
    else this->a = a;
    
}

void Color::set(uint32_t color)
{
    r = color>>24;
    g = color>>16;
    b = color>>8;
    a = color>>0;
}

void Color::setRGB(uint32_t color)
{
    r = color >> 16;
    g = color >> 8;
    b = color >> 0;
}

void Color::toInt32(uint32_t& color)
{
    color = 0;
    color |= r<<24;
    color |= g<<16;
    color |= b<<8;
    color |= a<<0;
}

void Color::toColorF(GLfloat* colorf)
{
    colorf[0] = r/255.0f;
    colorf[1] = g/255.0f;
    colorf[2] = b/255.0f;
    colorf[3] = a/255.0f;
}

void Color::multiply(const Color& v)
{
    r *= v.r/255.0f;
    g *= v.g/255.0f;
    b *= v.b/255.0f;
    a *= v.a/255.0f;
}

void Color::setRealOpacity(GLubyte v)
{
    r *= v/255.0f;
    g *= v/255.0f;
    b *= v/255.0f;
}

GradientColor::GradientColor()
:end(0xffffffff),vector(0)
{
}

GradientColor::GradientColor(const Color& start, const Color& e)
:start(start),end(e),vector(-1)
{
}

DE_END
