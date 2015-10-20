//
//  RTT.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "RTT.h"
#include "PaintEngine.h"
#include "Image.h"
#include "System.h"

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
        PaintEngine::GetInstance()->deleteFBO(1, &m_FBO);
    }
    SAFF_DELETE(m_displayFrame);
}


bool RTT::begin(int w,int h,Image* bg)
{
    if (m_displayFrame) {
        if (m_displayFrame->getTexture()->getWidth() != w ||
            m_displayFrame->getTexture()->getHeight() != h) {
            ImageInfo* frame = new ImageInfo();
            Texture* tex = new Texture();
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
        ImageInfo* frame = new ImageInfo();
        Texture* tex = new Texture();
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
    m_FBO = PaintEngine::GetInstance()->createFBO(m_displayFrame->getTexture()->getTextureId());
    
    PaintEngine::GetInstance()->resizeGL(PaintEngine::GetInstance()->getLayerWidth(),
                                      PaintEngine::GetInstance()->getLayerHeight());
    
    PaintEngine::GetInstance()->switchFBO(&m_oldFBO,m_FBO);
    PaintEngine::GetInstance()->clearColor(GL_COLOR_BUFFER_BIT,1,1,1,1);
    
    if (bg) {
        bg->update();
    }
    return true;
}

void RTT::end()
{
    PaintEngine::GetInstance()->switchFBO(NULL,m_oldFBO);
    PaintEngine::GetInstance()->resizeGL(System::GetInstance()->getDesktopWidth(),
                                      System::GetInstance()->getDesktopHeight());
}

DE_END
