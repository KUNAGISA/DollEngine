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
#include "GameObject.h"
#include "GLCanvas.h"

DE_BEGIN

Character::Character()
:m_textChanged(false)
,m_fontSize(DEFFONTSIZE)
,m_fontName(DEFFONT)
,m_text("")
{
    setCompName("Character");
}

Character::~Character()
{
    for (TextFrame* frame : m_allTextFrames) {
        SAFF_RELEASE(frame);
    }
    m_allTextFrames.clear();
}

void Character::setSizeToImageSize()
{
    updateText();
    
    if (m_allTextFrames.size() > 0) {
        m_paintHeight = m_fontSize;
        m_paintWidth = 0;
        for (TextFrame* frame : m_allTextFrames) {
            m_paintWidth += frame->getFont()->advance;
        }
    }
    else {
        m_paintWidth = 0;
        m_paintHeight = 0;
    }
}

void Character::update()
{
    setSizeToImageSize();
    if (m_allTextFrames.size() == 0) {
        return;
    }
    
    float ox,oy;
    if (getObject()) {
        ox = -getObject()->getAnchorX()*m_paintWidth;
        oy = -getObject()->getAnchorY()*m_paintHeight;
    }
    else {
        ox = 0;
        oy = m_paintHeight;
    }
    
    float lastX=0;
    for (TextFrame* frame : m_allTextFrames) {
        FontData* font = frame->getFont();
        Transform orgin;
        if (getObject()) {
            orgin.copy(getObject()->getTransInWorld());
        }
        Transform offst;
        offst.setX(lastX + font->bearingX +ox);
        float y = -(frame->getHeight()-font->bearingY)+oy;
        string fontname = frame->getCacheKey();
        offst.setY(y);
        offst.flush();
        orgin.setWidth(frame->getWidth());
        orgin.setHeight(frame->getHeight());
        orgin.transform(&offst);
        
        PaintConfig config;
        flushPaintConfig(config);
        config.trans = &orgin;
        config.frame = frame;
        config.width = frame->getWidth();
        config.height = frame->getHeight();
        GLCanvas::GetInstance()->paint(config);
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
        SAFF_RELEASE(frame);
    }
    m_allTextFrames.clear();
    vector<string> strs;
    Utf8ToVector(m_text,strs);
    for (auto iter = strs.begin();
         iter != strs.end(); ++iter) {
        TextFrame* frame = GLCache::GetInstance()->addText(*iter, m_fontName, m_fontSize);
        if (frame) {
            frame->retain();
            m_allTextFrames.push_back(frame);
        }
    }
}

DE_END
