//
//  GLTexture.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLTexture.h"
#include "PaintEngine.h"
#include "GLFunctions.h"

DE_BEGIN

GLTexture::GLTexture()
:m_retainCount(0)
,m_height(0)
,m_textureId(0)
,m_width(0)
{
    
}

GLTexture::~GLTexture()
{
    PaintEngine::GetInstance()->removeTextureCache(this);
    if (m_textureId) {
        glDeleteTextures(1, &m_textureId);
    }
}

bool GLTexture::initWithImage(GLImage* image)
{
    glGenTextures(1,&m_textureId);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
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

void GLTexture::retain()
{
    m_retainCount++;
}

void GLTexture::release()
{
    m_retainCount--;
    if (m_retainCount <= 0) {
        delete this;
    }
}

void GLTexture::bind(GLenum activeId)
{
    if (m_textureId) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }
}

void GLTexture::setTextureId(GLuint v)
{
    if (m_textureId) {
        glDeleteTextures(1, &m_textureId);
    }
    m_textureId = v;
}

DE_END

