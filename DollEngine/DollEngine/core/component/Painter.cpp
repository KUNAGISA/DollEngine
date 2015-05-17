//
//  Painter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Painter.h"
#include "GLCache.h"
#include "Device.h"
#include "GLCanvas.h"

DE_BEGIN

Painter::Painter()
:m_displayFrame(null)
{
    setCompName("Painter");
    m_type = COMP_PAINT;
    m_transform = new Transform();
    m_program = GLCanvas::GetInstance()->getProgram(DE::NORMAL_PROGRAM);
}

Painter::~Painter()
{
    SAFF_RELEASE(m_displayFrame);
    delete m_transform;
}

bool Painter::loadImages(const string& path,const string& plist)
{
    SpriteFrame* frame = GLCache::GetInstance()->addFrame(path);
    if (frame) {
        setDisplayFrame(frame);
        NEED_REDRAW;
        return true;
    }
    else {
        return false;
    }
}

Size Painter::getPaintSize()
{
    if (m_displayFrame) {
        return Size(m_displayFrame->getWidth(),m_displayFrame->getHeight());
    }
    else {
        return Size::Zero();
    }
}

void Painter::setDisplayFrame(DE::SpriteFrame *v)
{
    SAFF_RELEASE(m_displayFrame);
    m_displayFrame = v;
    SAFF_RETAIN(m_displayFrame);
}

static GLenum s_blendingSource = -1;
static GLenum s_blendingDest = -1;
void Painter::blendFunc(GLenum src,GLenum dst)
{
    if (src != s_blendingSource || dst != s_blendingDest)
    {
        s_blendingSource = src;
        s_blendingDest = dst;
        if (src == GL_ONE && dst == GL_ZERO)
        {
            glDisable(GL_BLEND);
        }
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(src, dst);
        }
    }
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
    if (!m_displayFrame) {
        return;
    }
    if (getObject()) {
        m_transform->copy(getObject()->getTransInWorld());
        m_transform->setWidth(m_displayFrame->getWidth());
        m_transform->setHeight(m_displayFrame->getHeight());
    }
    else {
        m_transform->copy(GLCanvas::GetInstance()->getGlobalTrans());
    }
    
    blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    
    GLCanvas::GetInstance()->paint(m_displayFrame, m_transform, &m_color, m_program);
}

DE_END