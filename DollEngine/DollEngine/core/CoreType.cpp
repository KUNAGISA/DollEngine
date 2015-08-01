//
//  CoreType.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreType.h"
#include "Transform.h"

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


GradientColor::GradientColor()
:end(0xffffffff),vector(0)
{
}

GradientColor::GradientColor(const Color& start, const Color& e)
:Color(start),end(e),vector(0)
{
}


void GLDrawData::setPos(float x, float y,float w,float h,Transform* trans)
{
    lb.vertex.v1 = lt.vertex.v1 = x;
    rb.vertex.v2 = lb.vertex.v2 = y;
    rb.vertex.v1 = rt.vertex.v1 = x+w;
    lt.vertex.v2 = rt.vertex.v2 = y+h;
    if (trans) {
        trans->transTo(lb.vertex.v1, lb.vertex.v2, &lb.vertex);
        trans->transTo(lt.vertex.v1, lt.vertex.v2, &lt.vertex);
        trans->transTo(rb.vertex.v1, rb.vertex.v2, &rb.vertex);
        trans->transTo(rt.vertex.v1, rt.vertex.v2, &rt.vertex);
    }
}

void GLDrawData::setFrameRect(float l,float t,float r,float b)
{
    lt.uv.v1 = lb.uv.v1 = l;
    rt.uv.v1 = rb.uv.v1 = r;
    lt.uv.v2 = rt.uv.v2 = t;
    lb.uv.v2 = rb.uv.v2 = b;
}

void GLDrawData::setInnerRect(float l,float r,float b,float t)
{
    float nl = (rt.uv.v1-lt.uv.v1) * l + lt.uv.v1;
    float nb = lb.uv.v2 - (lb.uv.v2-lt.uv.v2) * b;
    float nr = rt.uv.v1 - (rt.uv.v1-lt.uv.v1) * r;
    float nt = (lb.uv.v2-lt.uv.v2) * t + lt.uv.v2;
    lt.uv.v1 = lb.uv.v1 = nl;
    rt.uv.v1 = rb.uv.v1 = nr;
    lt.uv.v2 = rt.uv.v2 = nt;
    lb.uv.v2 = rb.uv.v2 = nb;
}

void GLDrawData::setStart(Color* color)
{
    color->toColorF((GLfloat*)&lt.color);
    color->toColorF((GLfloat*)&rt.color);
}

void GLDrawData::setEnd(Color* color)
{
    color->toColorF((GLfloat*)&lb.color);
    color->toColorF((GLfloat*)&rb.color);
}

DE_END
