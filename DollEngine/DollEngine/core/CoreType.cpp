//
//  CoreType.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreType.h"

DE_BEGIN

static Rect s_rect_zero = Rect(0,0,0,0);

Rect::Rect(float x,float y,float w,float h)
{
    set(x,y,w,h);
}

void Rect::set(float x,float y,float w,float h)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

const Rect& Rect::Zero()
{
    return s_rect_zero;
}

static Size s_size_zero = Size(0,0);

Size::Size(float w,float h)
{
    set(w,h);
}

void Size::set(float w,float h)
{
    this->width = w;
    this->height = h;
}

const Size& Size::Zero()
{
    return s_size_zero;
}

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

void Color::set(uint32_t color)
{
    r = color>>24;
    g = color>>16;
    b = color>>8;
    a = color>>0;
}

void Color::toColorF(GLfloat* colorf)
{
    colorf[0] = r/255.0f;
    colorf[1] = g/255.0f;
    colorf[2] = b/255.0f;
    colorf[3] = a/255.0f;
}


GradientColor::GradientColor()
:end(0xffffffff),horizontal(false)
{
}

GradientColor::GradientColor(const Color& start, const Color& e)
:Color(start),end(e),horizontal(false)
{
}

DE_END
