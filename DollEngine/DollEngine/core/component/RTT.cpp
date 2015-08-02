//
//  RTT.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "RTT.h"
#include "GLCanvas.h"
#include "GameObject.h"
#include "Painter.h"

DE_BEGIN

RTT::RTT()
:m_FBO(0)
,m_oldFBO(0)
{
    m_flipY = true;
}

RTT::~RTT()
{
    if (m_FBO) {
        glDeleteFramebuffers(1, &m_FBO);
    }
    SAFF_DELETE(m_displayFrame);
}


bool RTT::loadRender(GameObject* obj,int w,int h,Painter* bg)
{
    if (!obj) {
        return false;
    }
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_oldFBO);
    if (m_displayFrame) {
        if (m_displayFrame->getTexture()->getWidth() != w ||
            m_displayFrame->getTexture()->getHeight() != h) {
            SpriteFrame* frame = new SpriteFrame();
            GLTexture* tex = new GLTexture();
            if(!tex->initWithSize(w, h)){
                delete tex;
                delete frame;
                return false;
            }
            m_paintWidth = w;
            m_paintHeight = h;
            delete m_displayFrame;
            m_displayFrame = frame;
            m_displayFrame->setTexture(tex);
        }
    }
    else {
        SpriteFrame* frame = new SpriteFrame();
        GLTexture* tex = new GLTexture();
        if(!tex->initWithSize(w, h)){
            delete tex;
            delete frame;
            return false;
        }
        m_paintWidth = w;
        m_paintHeight = h;
        m_displayFrame = frame;
        m_displayFrame->setTexture(tex);
    }
    GLint oldRBO;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
    
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_displayFrame->getTexture()->getTextureId(), 0);
    ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_oldFBO);
    
    GameObject* parent = obj->getParent();
    obj->setParent(null);
    
    //begin
//    glViewport(0, 0, DEApplication->getDeviceWidth(), DEApplication->getDeviceHeight());
    float deviceW = DEApplication->getDeviceWidth();
    float deviceH = DEApplication->getDeviceHeight();
    DEApplication->setDeviceSize(GLCanvas::GetInstance()->getLayerWidth(), GLCanvas::GetInstance()->getLayerHeight());
    GLCanvas::GetInstance()->resizeGL();
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1,1,1,1);
    
    if (bg) {
        bg->update();
    }
    obj->visit();
    
    //end
    glBindFramebuffer(GL_FRAMEBUFFER, m_oldFBO);
    CHECK_GL_ERROR;
    DEApplication->setDeviceSize(deviceW,deviceH);
    GLCanvas::GetInstance()->resizeGL();
    obj->setParent(parent);
    return true;
}

DE_END