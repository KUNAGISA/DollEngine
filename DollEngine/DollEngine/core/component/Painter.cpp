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
#include "GLPainter.h"
#include "GameObject.h"
#include "GLCanvas.h"

DE_BEGIN

Painter::Painter()
:m_displayFrame(null)
,m_scale9(false)
,m_colorRect(false)
,m_paintHeight(0)
,m_paintWidth(0)
,m_blendSrc(GL_ONE)
,m_blendDst(GL_ONE_MINUS_SRC_ALPHA)
{
    setCompName("Painter");
    m_type = COMP_PAINT;
    m_color = new GradientColor();
    m_program = GLPainter::GetInstance()->getProgram("normal");
}

Painter::~Painter()
{
    SAFF_RELEASE(m_displayFrame);
    SAFF_DELETE(m_color);
}

bool Painter::loadImages(const string& path,const string& plist)
{
    SpriteFrame* frame = GLCache::GetInstance()->addFrame(path);
    m_colorRect = false;
    setPaintSizeToImageSize();
    if (frame) {
        setDisplayFrame(frame);
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
        NEED_REDRAW;
        return true;
    }
    else {
        return false;
    }
}

void Painter::setPaintSizeToImageSize()
{
    if (m_colorRect) {
        return;
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
    m_color->set(color);
    NEED_REDRAW;
}

void Painter::setGradientColor(uint32_t start,uint32_t end,int vector)
{
    m_gradient = true;
    m_color->set(start);
    m_color->vector = vector;
    m_color->end.set(end);
    NEED_REDRAW;
}

void Painter::setOpacity(GLubyte o)
{
    m_color->a = o;
    if (m_gradient) {
        m_color->end.a = o;
    }
    NEED_REDRAW;
}

void Painter::update()
{
    if (!getObject()) {
        return;
    }
    if (!m_displayFrame) {
        return;
    }
    if (m_scale9) {
        
    }
    else {
        updateWithFrame();
    }
}

void Painter::updateWithFrame()
{
    PaintConfig config;
    config.frame = m_displayFrame;
    config.trans = getObject()->getTransInWorld();
    config.color = m_color;
    if (m_gradient) {
        config.end = &m_color->end;
        config.gradVector = m_color->vector;
    }
    else {
        config.end = null;
    }
    config.program = m_program;
    config.width = m_paintWidth;
    config.height = m_paintHeight;
    config.blendSrc = m_blendSrc;
    config.blendDst = m_blendDst;
    GLPainter::GetInstance()->paint(config);
}


DE_END