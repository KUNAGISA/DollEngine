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

void RTT::init(int w,int h)
{
    if (m_info && m_info->getTexture()) {
        if (m_info->getTexture()->getWidth() != w ||
            m_info->getTexture()->getHeight() != h) {
            ImageInfo* frame = new ImageInfo();
            Texture* tex = new Texture();
            if(!tex->initWithSize(w, h)){
                delete tex;
                delete frame;
                return;
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
            return ;
        }
        m_info = frame;
        m_info->setTexture(tex);
        setPaintSize(w,h);
        PaintEngine::GetInstance()->createFBO(m_info->getTexture()->getTextureId(),&m_oldFBO,&m_FBO);
    }
}

bool RTT::begin(float r,float g,float b,float a)
{
    PaintEngine::GetInstance()->resize(PaintEngine::GetInstance()->getLayerWidth(),
                                      PaintEngine::GetInstance()->getLayerHeight());
    PaintEngine::GetInstance()->switchFBO(&m_oldFBO,m_FBO);
    PaintEngine::GetInstance()->clearColor(GL_COLOR_BUFFER_BIT,r,g,b,a);
    
    return true;
}

void RTT::end()
{
    PaintEngine::GetInstance()->paint();
    PaintEngine::GetInstance()->switchFBO(NULL,m_oldFBO);
    
    PaintEngine::GetInstance()->resize(Window::GetInstance()->getWidth(),
                                      Window::GetInstance()->getHeight());
}

bool RTT::saveToFile(const String& path,int tw, int th)
{
    if(!m_info || !m_info->getTexture()) {
        return false;
    }
    int w = m_info->getTexture()->getWidth();
    int h = m_info->getTexture()->getHeight();
    if(tw <= 0) tw = w;
    if(th <= 0) th = h;
    IOData* data = new IOData();
    
    data->initWithSize(w*h*4);
    
    PaintEngine::GetInstance()->switchFBO(&m_oldFBO,m_FBO);
    PaintEngine::GetInstance()->readPixmap(w,h,data->getBuffer());
    PaintEngine::GetInstance()->switchFBO(NULL,m_oldFBO);
    
    PictureData picture;
    picture.setData(data);
    picture.setWidth(w);
    picture.setHeight(h);
    return picture.saveImage(path,tw,th);
}

void RTT::paint(Transform* trans)
{
    Image::paint(trans);
}

DE_END
