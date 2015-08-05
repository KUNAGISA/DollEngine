//
//  Painter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Painter.h"
#include "GLCache.h"
#include "Application.h"
#include "GameObject.h"
#include "GLCanvas.h"
#include "Storages.h"

DE_BEGIN

Painter::Painter()
:m_displayFrame(null)
,m_scale9(false)
,m_colorRect(false)
,m_paintHeight(0)
,m_paintWidth(0)
,m_blendSrc(GL_ONE)
,m_blendDst(GL_ONE_MINUS_SRC_ALPHA)
,m_gradient(false)
,m_scale9B(1.0/3)
,m_scale9L(1.0/3)
,m_scale9R(1.0/3)
,m_scale9T(1.0/3)
,m_color(0xffffffff)
,m_program(null)
,m_flipY(false)
,m_opacity(0xff)
,m_endColor(0xffffffff)
,m_endOpacity(0xff)
{
    setCompName("Painter");
    m_type = COMP_PAINT;
    m_program = GLCanvas::GetInstance()->getProgram("normal");
}

Painter::~Painter()
{
    SAFF_RELEASE(m_displayFrame);
}

bool Painter::loadImages(const string& path,const string& plist)
{
    SpriteFrame* frame = GLCache::GetInstance()->addFrame(path);
    if (frame) {
        m_colorRect = false;
        setDisplayFrame(frame);
        setSizeToImageSize();
        NEED_REDRAW;
        return true;
    }
    else {
        return false;
    }
}

bool Painter::loadImageWithMargin(const string& path,float l,float r,float t,float b)
{
    SpriteFrame* frame = GLCache::GetInstance()->addFrame(path);
    Rect rect(l*frame->getWidth(),
              t*frame->getHeight(),
              (1-l-r)*frame->getWidth(),
              (1-t-b)*frame->getHeight());
    frame = GLCache::GetInstance()->addFrame(path,rect);
    if (frame) {
        m_colorRect = false;
        setDisplayFrame(frame);
        setSizeToImageSize();
        NEED_REDRAW;
        return true;
    }
    else {
        return false;
    }
}

bool Painter::loadSize(int w,int h,int r)
{
    SpriteFrame* frame = GLCache::GetInstance()->addFrame(r);
    m_colorRect=true;
    m_paintWidth = w;
    m_paintHeight = h;
    if (frame) {
        setDisplayFrame(frame);
        setSizeToImageSize();
        NEED_REDRAW;
        return true;
    }
    else {
        return false;
    }
}

void Painter::setSizeToImageSize()
{
    if (m_colorRect) {
        
    }
    else {
        if (m_displayFrame) {
            m_paintWidth = m_displayFrame->getWidth();
            m_paintHeight = m_displayFrame->getHeight();
        }
        else {
            m_paintWidth = 0;
            m_paintHeight = 0;
        }
    }
    if(getObject()){
        getObject()->setWidth(m_paintWidth);
        getObject()->setHeight(m_paintHeight);
    }
}

void Painter::setDisplayFrame(DE::SpriteFrame *v)
{
    SAFF_RELEASE(m_displayFrame);
    m_displayFrame = v;
    SAFF_RETAIN(m_displayFrame);
}


void Painter::setColor(uint32_t color)
{
    m_gradient = false;
    m_color = color;
    NEED_REDRAW;
}

void Painter::setGradientColor(uint32_t start,uint32_t end,int vector)
{
    m_gradient = true;
    m_realColor.vector = vector;
    m_color = start;
    m_endColor = end;
    NEED_REDRAW;
}

void Painter::setOpacity(GLubyte o)
{
    m_opacity = o;
    if (m_gradient) {
        m_endOpacity = o;
    }
    NEED_REDRAW;
}

void Painter::update()
{
    if (!m_displayFrame) {
        return;
    }
    if (m_scale9) {
        updateWithScale9();
    }
    else {
        updateWithFrame();
    }
}

void Painter::updateWithScale9()
{
    PaintConfig config;
    flushPaintConfig(config);
    Scale9Config scfg = {m_scale9L,m_scale9B,m_scale9R,m_scale9T};
    config.scale9 = &scfg;
    GLCanvas::GetInstance()->paint(config);
}

void Painter::updateWithFrame()
{
    PaintConfig config;
    flushPaintConfig(config);
    GLCanvas::GetInstance()->paint(config);
}

void Painter::flushPaintConfig(PaintConfig& config)
{
    config.frame = m_displayFrame;
    m_realColor.set(m_color);
    m_realColor.a = m_opacity;
    if (getObject()) {
        config.trans = getObject()->getTransInWorld();
        m_realColor.multiply(getObject()->m_realColor);
    }
    else {
        config.trans = null;
    }
    config.start = &m_realColor;
    if (m_gradient) {
        m_realColor.end.set(m_endColor);
        m_realColor.end.a = m_endOpacity;
        if (getObject()) {
            m_realColor.end.multiply(getObject()->m_realColor);
        }
        config.end = &m_realColor.end;
        config.gradVector = m_realColor.vector;
    }
    else {
        config.end = null;
    }
    config.program = m_program;
    config.width = m_paintWidth;
    config.height = m_paintHeight;
    config.blendSrc = m_blendSrc;
    config.blendDst = m_blendDst;
    config.scale9 = null;
    config.flipY = m_flipY;
}

DE_END