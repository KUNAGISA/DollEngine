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
#include "Window.h"

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
    SAFF_DELETE(m_info);
}


bool RTT::begin(int w,int h)
{
    if (m_info && m_info->getTexture()) {
        if (m_info->getTexture()->getWidth() != getPaintWidth() ||
            m_info->getTexture()->getHeight() != getPaintHeight()) {
            ImageInfo* frame = new ImageInfo();
            Texture* tex = new Texture();
            if(!tex->initWithSize(w, h)){
                delete tex;
                delete frame;
                return false;
            }
            delete m_info;
            m_info = frame;
            m_info->setTexture(tex);
            setPaintSize(w,h);
            PaintEngine::GetInstance()->createFBO(m_info->getTexture()->getTextureId(),&m_oldFBO,&m_FBO);
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
        m_info = frame;
        m_info->setTexture(tex);
        setPaintSize(w,h);
        PaintEngine::GetInstance()->createFBO(m_info->getTexture()->getTextureId(),&m_oldFBO,&m_FBO);
    }
    
    PaintEngine::GetInstance()->resize(PaintEngine::GetInstance()->getLayerWidth(),
                                      PaintEngine::GetInstance()->getLayerHeight());
    
    PaintEngine::GetInstance()->switchFBO(&m_oldFBO,m_FBO);
    PaintEngine::GetInstance()->clearColor(GL_COLOR_BUFFER_BIT,0,0,0,1);
    
    return true;
}

void RTT::end()
{
    PaintEngine::GetInstance()->paint();
    PaintEngine::GetInstance()->switchFBO(NULL,m_oldFBO);
    PaintEngine::GetInstance()->resize(Window::GetInstance()->getWidth(),
                                      Window::GetInstance()->getHeight());
    
}

void RTT::paint(Transform* trans)
{
    Image::paint(trans);
}

DE_END
