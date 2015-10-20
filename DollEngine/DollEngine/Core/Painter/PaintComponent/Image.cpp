//
//  Image.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Image.h"
#include "GLCache.h"
#include "System.h"
#include "PaintEngine.h"
#include "Storages.h"

DE_BEGIN

Image::Image()
:m_displayFrame(NULL)
,m_paintHeight(0)
,m_paintWidth(0)
,m_blendSrc(GL_ONE)
,m_blendDst(GL_ONE_MINUS_SRC_ALPHA)
,m_gradient(false)
,m_color(0xffffffff)
,m_program(NULL)
,m_flipY(false)
,m_opacity(0xff)
,m_endColor(0xffffffff)
,m_endOpacity(0xff)
{
    setProgram("normal");
}

Image::~Image()
{
    SAFF_DELETE(m_displayFrame);
}

bool Image::loadImages(const String& path,const String& plist)
{
    ImageInfo* frame = new ImageInfo();
    if(frame->loadWithFile(path,plist)) {
        setDisplayFrame(frame);
        setSizeToImageSize();
        NEED_REDRAW;
        return true;
    }
    else {
        delete frame;
        return false;
    }
}
void Image::setDrawSize(float w,float h)
{
    if(m_displayFrame){
        m_displayFrame->setDrawSize(w,h);
    }
}

void Image::clipRect(float x,float y,float w,float h)
{
    
}

void Image::setScale9(float l,float t,float r,float b)
{
    
}

void Image::setSizeToImageSize()
{
    if(m_displayFrame){
        m_displayFrame->setDrawSize(m_displayFrame->getWidth(),m_displayFrame->getHeight());
    }
}

void Image::setIsScale9(bool v)
{
    if(m_displayFrame){
        m_displayFrame->setIsScale9(v);
    }
}

void Image::setProgram(const String& name)
{
    m_program = PaintEngine::GetInstance()->getProgram(name);
}

void Image::setDisplayFrame(DE::ImageInfo *v)
{
    SAFF_DELETE(m_displayFrame);
    m_displayFrame = v;
}


void Image::setColor(uint32_t color)
{
    m_gradient = false;
    m_color = color;
    NEED_REDRAW;
}

void Image::setGradientColor(uint32_t start,uint32_t end,int vector)
{
    m_gradient = true;
    m_realColor.vector = vector;
    m_color = start;
    m_endColor = end;
    NEED_REDRAW;
}

void Image::setOpacity(GLubyte o)
{
    m_opacity = o;
    if (m_gradient) {
        m_endOpacity = o;
    }
    NEED_REDRAW;
}

void Image::update()
{
    if (!m_displayFrame) {
        return;
    }
    if (m_scale9) {
        updateWithScale9();
    }
    else {
        updateWithFrame();
    }
}

void Image::updateWithScale9()
{
    PaintConfig config;
    flushPaintConfig(config);
    Scale9Config scfg = {m_scale9L,m_scale9B,m_scale9R,m_scale9T};
    config.scale9 = &scfg;
    PaintEngine::GetInstance()->paint(config);
}

void Image::updateWithFrame()
{
    PaintConfig config;
    flushPaintConfig(config);
    PaintEngine::GetInstance()->paint(config);
}

void Image::flushPaintConfig(PaintConfig& config)
{
    config.frame = m_displayFrame;
    m_realColor.set(m_color);
    m_realColor.a = m_opacity;
//    if (getObject()) {
//        config.trans = getObject()->getTransInWorld();
//        m_realColor.multiply(getObject()->m_realColor);
//    }
//    else {
//        config.trans = NULL;
//    }
    config.start = &m_realColor;
    if (m_gradient) {
        m_realColor.end.set(m_endColor);
        m_realColor.end.a = m_endOpacity;
//        if (getObject()) {
//            m_realColor.end.multiply(getObject()->m_realColor);
//        }
        config.end = &m_realColor.end;
        config.gradVector = m_realColor.vector;
    }
    else {
        config.end = NULL;
    }
    config.program = m_program;
    config.width = m_paintWidth;
    config.height = m_paintHeight;
    config.blendSrc = m_blendSrc;
    config.blendDst = m_blendDst;
    config.scale9 = NULL;
    config.flipY = m_flipY;
}

DE_END
