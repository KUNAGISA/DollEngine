//
//  Painter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Painter.h"
#include "PaintEngine.h"
#include "Device.h"

DE_BEGIN

Painter::Painter()
:m_displayFrame(null)
{
    setCompName("Painter");
    m_type = COMP_PAINT;
    m_transform = new Transform();
    m_program = PaintEngine::GetInstance()->getProgram(DE::NORMAL_PROGRAM);
}

bool Painter::loadImages(const string& path,const string& plist)
{
    SpriteFrame* frame = PaintEngine::GetInstance()->addFrame(path);
    if (frame) {
        setDisplayFrame(frame);
        NEED_REDRAW;
        return true;
    }
    else {
        return false;
    }
}

void Painter::setDisplayFrame(DE::SpriteFrame *v)
{
    SAFF_RELEASE(m_displayFrame);
    m_displayFrame = v;
    SAFF_RETAIN(m_displayFrame);
}

void Painter::setColor(GLubyte r,GLubyte g, GLubyte b)
{
    m_color.set(r, g, b);
}

void Painter::setColor(GLubyte r,GLubyte g, GLubyte b, GLubyte a)
{
    m_color.set(r, g, b, a);
}

void Painter::setColor(uint32_t color)
{
    m_color.set(color);
}

void Painter::setOpacity(GLubyte o)
{
    m_color.a = o;
}

void Painter::update()
{
    if (getObject()) {
        m_transform->copy(getObject()->getTransInWorld());
        m_transform->setWidth(m_displayFrame->getWidth());
        m_transform->setHeight(m_displayFrame->getHeight());
    }
    else {
        m_transform->copy(PaintEngine::GetInstance()->getGlobalTrans());
    }
    
    PaintEngine::GetInstance()->paint(m_displayFrame, m_transform, &m_color, m_program);
}

DE_END