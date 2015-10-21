//
//  Character.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Character.h"
#include "GLCache.h"
#include "TextFrame.h"
#include "PaintEngine.h"

DE_BEGIN

Character::Character()
:m_textChanged(false)
,m_fontSize(DEFFONTSIZE)
,m_fontName(DEFFONT)
,m_text("")
{
}

Character::~Character()
{
    for (TextFrame* frame : m_allTextFrames) {
        delete frame;
    }
    m_allTextFrames.clear();
}

void Character::setSizeToImageSize()
{
    updateText();
    
//    if (m_allTextFrames.size() > 0) {
//        m_paintHeight = m_fontSize;
//        m_paintWidth = 0;
//        for (TextFrame* frame : m_allTextFrames) {
//            m_paintWidth += frame->getFont()->advance;
//        }
//    }
//    else {
//        m_paintWidth = 0;
//        m_paintHeight = 0;
//    }
}

void Character::update()
{
    setSizeToImageSize();
    if (m_allTextFrames.size() == 0) {
        return;
    }
    
    float lastX=0;
    for (TextFrame* frame : m_allTextFrames) {
        FontData* font = frame->getFont();
        Transform orgin;
//        if (getObject()) {
//            orgin.copy(getObject()->getTransInWorld());
//        }
        Transform offst;
        offst.setX(lastX + font->bearingX);
        float y = -(frame->getHeight()-font->bearingY);
        offst.setY(y);
        offst.setAnchorX(0);
        offst.setAnchorY(0);
        offst.flush();
        orgin.setWidth(frame->getWidth());
        orgin.setHeight(frame->getHeight());
        orgin.transform(&offst);
        
        PaintConfig config;
        flushPaintConfig(config);
        config.trans = &orgin;
        config.info = frame;
//        config.width = frame->getWidth();
//        config.height = frame->getHeight();
        PaintEngine::GetInstance()->paint(config);
        lastX += frame->getFont()->advance;
    }
}

void Character::updateText()
{
    if (!m_textChanged) {
        return;
    }
    
    m_textChanged=false;
    
    for (TextFrame* frame : m_allTextFrames) {
        delete frame;
    }
    m_allTextFrames.clear();
    for (int i=0;i!=m_text.size();++i) {
        TextFrame* frame = GLCache::GetInstance()->addText(m_text[i], m_fontName, m_fontSize);
        if (frame) {
            m_allTextFrames.push_back(frame);
        }
    }
}

DE_END