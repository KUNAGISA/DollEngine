//
//  RTT.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "RTT.h"
#include "GLCanvas.h"
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
        DI->deleteFBO(1, &m_FBO);
    }
    SAFF_DELETE(m_displayFrame);
}


bool RTT::begin(int w,int h,Painter* bg)
{
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
    m_FBO = DI->createFBO(m_displayFrame->getTexture()->getTextureId());
    
    DESystem->setDeviceSize(GLCanvas::GetInstance()->getLayerWidth(), GLCanvas::GetInstance()->getLayerHeight());
    GLCanvas::GetInstance()->resizeGL();
    
    DI->switchFBO(&m_oldFBO,m_FBO);
    DI->clearColor(GL_COLOR_BUFFER_BIT,1,1,1,1);
    
    if (bg) {
        bg->update();
    }
    return true;
}

void RTT::end()
{
    float deviceW = DESystem->getDeviceWidth();
    float deviceH = DESystem->getDeviceHeight();
    DI->switchFBO(null,m_oldFBO);
    CHECK_GL_ERROR;
    DESystem->setDeviceSize(deviceW,deviceH);
    GLCanvas::GetInstance()->resizeGL();
}

DE_END
