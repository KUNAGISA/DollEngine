//
//  SpriteFrame.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-19.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "SpriteFrame.h"

SpriteFrame::SpriteFrame()
:m_texture(null)
,m_retainCount(0)
{
    memset(m_glCoord, 0,8*sizeof(GLfloat));
}

SpriteFrame::~SpriteFrame()
{
    SAFF_RELEASE_NULL(m_texture);
}

bool SpriteFrame::initWithTexture(Texture2D* tex,const kRect& rect)
{
    setTexture(tex);
    setRect(rect);
    return true;
}

bool SpriteFrame::initWithTexture(Texture2D* tex)
{
    if (!tex) {
        setTexture(null);
        return true;
    }
    return initWithTexture(tex,{0,0,(float)tex->getWidth(),(float)tex->getHeight()});
}

float SpriteFrame::getWidth()
{
    return m_rect.width;
}

float SpriteFrame::getHeight()
{
    return m_rect.height;
}


//static GLfloat coordinates[] = {
//    0,0,
//    0,1,
//    1,0,
//    1,1};

void SpriteFrame::setRect(kRect v)
{
    if (m_texture)
    {
        m_rect = v;
        m_glCoord[0] = v.left/m_texture->getWidth();
        m_glCoord[1] = v.top/m_texture->getHeight();
        m_glCoord[2] = m_glCoord[0];
        m_glCoord[3] = (v.top+v.height)/m_texture->getHeight();
        m_glCoord[4] = (v.left+v.width)/m_texture->getWidth();
        m_glCoord[5] = m_glCoord[1];
        m_glCoord[6] = m_glCoord[4];
        m_glCoord[7] = m_glCoord[3];
    }
    else
    {
        m_rect = {0,0,0,0};
        memset(m_glCoord, 0,8*sizeof(GLfloat));
    }
}

void SpriteFrame::setTexture(Texture2D* tex)
{
    SAFF_RELEASE_NULL(m_texture);
    m_texture=tex;
    SAFF_RETAIN(m_texture);
}

void SpriteFrame::retain()
{
    ++m_retainCount;
}

void SpriteFrame::release()
{
    --m_retainCount;
}
