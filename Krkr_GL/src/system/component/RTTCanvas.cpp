//
//  RTTCanvas.cpp
//  Krkr_GL
//
//  Created by DollStudio on 15/1/10.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "RTTCanvas.h"
#include "Object.h"
#include "PaintEngine.h"

RTTCanvas::RTTCanvas()
:m_height(0)
,m_width(0)
,m_opacity(1)
,m_spriteFrame(null)
,m_sizeChanged(false)
,m_program(null)
,m_FBO(0)
,m_lastFBO(0)
{
    setComName(L"RTTCanvas");
    m_program = PaintEngine::GetInstance()->getDefaultProgram();
    setEnabled(true);
}

RTTCanvas::~RTTCanvas()
{
    SAFF_RELEASE(m_spriteFrame);
}

void RTTCanvas::render(Object *orginNode, float x, float y)
{
    if (m_sizeChanged)
    {
        m_sizeChanged = false;
        
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_lastFBO);
        
        Texture2D* tex = new Texture2D();
        Image* image = new Image();
        IOData* iodata = new IOData();
        iodata->initWithSize((int)m_width*(int)m_height*4);
        iodata->clearBuffer();
        image->setData(iodata);
        image->setWidth(m_width);
        image->setHeight(m_height);
        tex->initWithImage(image);
        
        GLint oldRBO;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
        
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->getTexId(), 0);
        
        SAFF_RELEASE(m_spriteFrame);
        m_spriteFrame = new SpriteFrame();
        m_spriteFrame->initWithTexture(tex);
        tex->setAutoRelease(true);
        
        delete image;
        
        glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_lastFBO);
    }
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_lastFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    
    GLfloat	clearColor[4] = {0.0f,0.0f,0.0f,0.0f};
    glGetFloatv(GL_COLOR_CLEAR_VALUE,clearColor);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    
    Object* oldParent = orginNode->getParent();
    float oldX = orginNode->getLeft();
    float oldY = orginNode->getTop();
    bool oldVisible = orginNode->getVisible();
    orginNode->setLeft(x);
    orginNode->setTop(y);
    orginNode->setParent(null);
    orginNode->setVisible(true);
    orginNode->visit();
    glBindFramebuffer(GL_FRAMEBUFFER, m_lastFBO);
    orginNode->setLeft(oldX);
    orginNode->setTop(oldY);
    orginNode->setParent(oldParent);
    orginNode->setVisible(oldVisible);
}

void RTTCanvas::trigger()
{
    if (!m_enabled || !m_spriteFrame || !getObject() || !m_program) {
        return;
    }
    
    Transform* trans = getObject()->getWorldTrans();
    if (trans)
    {
        float opacity = getObject()->getRealyOpacity()*m_opacity;
        Vector4F color(opacity,opacity,opacity,opacity);
        Vector2F imageSize(m_spriteFrame->getWidth(),m_spriteFrame->getHeight());
        
        PaintEngine::GetInstance()->draw(trans,m_spriteFrame, m_program,imageSize,color,true);
    }
}


