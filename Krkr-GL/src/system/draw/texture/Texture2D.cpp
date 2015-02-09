//
//  Texture2D.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-19.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Texture2D.h"

Texture2D::Texture2D()
:m_width(0)
,m_height(0)
,m_retainCount(0)
,m_texId(0)
,m_autoRelease(false)
{
    
}

Texture2D::~Texture2D()
{
    if (m_texId) {
        glDeleteTextures(1, &m_texId);
    }
}

bool Texture2D::initWithImage(Image* image)
{
    glGenTextures(1,&m_texId);
    glBindTexture(GL_TEXTURE_2D,m_texId);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->getData()->getBuffer() );
    setWidth(image->getWidth());
    setHeight(image->getHeight());
    CHECK_GL_ERROR;
    return true;
}

void Texture2D::retain()
{
    ++m_retainCount;
}

void Texture2D::release()
{
    --m_retainCount;
    if (m_autoRelease && m_retainCount <=0 ) {
        delete this;
    }
}