//
//  Types.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreTypes.h"
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
    GLfloat c[4];
    color->toColorF(c);
    c[0] *= c[3];
    c[1] *= c[3];
    c[2] *= c[3];
    memcpy(&lt.color, c, sizeof(lt.color));
    memcpy(&rt.color, c, sizeof(rt.color));
}

void GLDrawData::setEnd(Color* color)
{
    GLfloat c[4];
    color->toColorF(c);
    c[0] *= c[3];
    c[1] *= c[3];
    c[2] *= c[3];
    memcpy(&lb.color, c, sizeof(lb.color));
    memcpy(&rb.color, c, sizeof(rb.color));
}

DE_END
