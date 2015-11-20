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
,m_startColor(0xffffff)
,m_startOpacity(0xff)
,m_endColor(0xffffff)
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
        resetPaintSize();
        NEED_REDRAW;
        return true;
    }
    else {
        delete info;
        DM("图片加载失败");
        return false;
    }
}
void Image::setPaintSize(float w,float h)
{
    if(!m_info){
        DM("[setPaintSize]尚未载入图片");
        return;
    }
    m_info->setPaintSize(w,h);
}

void Image::clipRect(float x,float y,float w,float h)
{
    if(!m_info){
        DM("[clipRect]尚未载入图片");
        return;
    }
    m_info->clipRect(x,y,w,h);
    resetPaintSize();
}

void Image::setScale9(float l,float t,float r,float b)
{
    
}

void Image::resetPaintSize()
{
    if(m_info){
        m_info->resetPaintSize();
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

void Image::paint(Transform* trans)
{
    if (!m_info) {
        return;
    }
    PaintConfig config;
    config.trans = trans;
    flushPaintConfig(config);
    PaintEngine::GetInstance()->preparePaint(config);
}

void Image::flushPaintConfig(PaintConfig& config)
{
    config.info = m_info;
    config.info->setColor(m_startColor,m_endColor,m_startOpacity,m_endOpacity);
    config.program = m_program;
    config.blendSrc = m_blendSrc;
    config.blendDst = m_blendDst;
    config.flipX = m_flipX;
    config.flipY = m_flipY;
}

DE_END
