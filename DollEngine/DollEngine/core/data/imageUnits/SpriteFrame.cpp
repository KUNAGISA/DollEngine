//
//  SpriteFrame.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "SpriteFrame.h"
#include "GLCache.h"

DE_BEGIN
SpriteFrame::SpriteFrame()
:m_texture(NULL)
,m_rect(Rect::Zero())
,m_retainCount(0)
{
    
}

SpriteFrame::~SpriteFrame()
{
    GLCache::GetInstance()->removeSpriteFrameCache(this);
    m_texture->release();
}

void SpriteFrame::retain()
{
    m_retainCount++;
}

void SpriteFrame::release()
{
    m_retainCount--;
    if (m_retainCount <= 0) {
        delete this;
    }
}

void SpriteFrame::setTexture(GLTexture* tex)
{
    if(m_texture) {
        m_texture->release();
    }
    m_texture = tex;
    if(m_texture) {
        m_texture->retain();
        setRect(Rect(0,0,m_texture->getWidth(),m_texture->getHeight()));
    }
}

void SpriteFrame::setRect(const DE::Rect &v)
{
    if (m_texture)
    {
        m_rect = v;
        m_glCoord[0] = v.x/m_texture->getWidth();
        m_glCoord[1] = v.y/m_texture->getHeight();
        m_glCoord[2] = m_glCoord[0];
        m_glCoord[3] = (v.x+v.height)/m_texture->getHeight();
        m_glCoord[4] = (v.y+v.width)/m_texture->getWidth();
        m_glCoord[5] = m_glCoord[3];
        m_glCoord[6] = m_glCoord[4];
        m_glCoord[7] = m_glCoord[1];
    }
}

DE_END
