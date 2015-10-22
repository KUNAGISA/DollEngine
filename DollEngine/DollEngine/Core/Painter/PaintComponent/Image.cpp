//
//  Image.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Image.h"
#include "System.h"
#include "PaintEngine.h"
#include "Storages.h"

DE_BEGIN

Image::Image()
:m_info(NULL)
,m_blendSrc(GL_ONE)
,m_blendDst(GL_ONE_MINUS_SRC_ALPHA)
,m_program(NULL)
,m_flipY(false)
,m_flipX(false)
,m_startColor(0xffffffff)
,m_startOpacity(0xff)
,m_endColor(0xffffffff)
,m_endOpacity(0xff)
{
    setProgram("normal");
}

Image::~Image()
{
    SAFF_DELETE(m_info);
}

bool Image::loadImages(const String& path,const String& plist)
{
    ImageInfo* info = new ImageInfo();
    if(info->loadWithFile(path,plist)) {
        setInfo(info);
        setSizeToImageSize();
        NEED_REDRAW;
        return true;
    }
    else {
        delete info;
        return false;
    }
}
void Image::setDrawSize(float w,float h)
{
    if(!m_info){
        EM("尚未载入图片");
        return;
    }
    m_info->setDrawSize(w,h);
}

void Image::clipRect(float x,float y,float w,float h)
{
    if(!m_info){
        EM("尚未载入图片");
        return;
    }
    if(w + x > m_info->getWidth()) w = m_info->getWidth()-x;
    if(h + y > m_info->getHeight()) h = m_info->getHeight()-y;
    Rect orgin = m_info->getOrginRect();
    m_info->setOrginRect(orgin.x+x,orgin.y+y,w,h);
}

void Image::setScale9(float l,float t,float r,float b)
{
    
}

void Image::setSizeToImageSize()
{
    if(m_info){
        m_info->setDrawSize(m_info->getWidth(),m_info->getHeight());
    }
}

void Image::setIsScale9(bool v)
{
    if(m_info){
        m_info->setIsScale9(v);
    }
}

void Image::setProgram(const String& name)
{
    m_program = PaintEngine::GetInstance()->getProgram(name);
}

void Image::setInfo(DE::ImageInfo *v)
{
    SAFF_DELETE(m_info);
    m_info = v;
}

void Image::draw(Transform* trans)
{
    if (!m_info) {
        return;
    }
    PaintConfig config;
    config.trans = trans;
    flushPaintConfig(config);
    PaintEngine::GetInstance()->paint(config);
}


void Image::flushPaintConfig(PaintConfig& config)
{
    config.info = m_info;
    config.program = m_program;
    config.blendSrc = m_blendSrc;
    config.blendDst = m_blendDst;
    config.flipX = m_flipX;
    config.flipY = m_flipY;
}

DE_END
