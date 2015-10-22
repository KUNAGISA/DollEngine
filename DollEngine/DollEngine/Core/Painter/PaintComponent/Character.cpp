//
//  Character.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Character.h"
#include "CharacterInfo.h"
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
    for (CharacterInfo* frame : m_characterInfos) {
        delete frame;
    }
    m_characterInfos.clear();
}

void Character::setSizeToImageSize()
{
    updateText();
    
//    if (m_characterInfos.size() > 0) {
//        m_paintHeight = m_fontSize;
//        m_paintWidth = 0;
//        for (CharacterInfo* frame : m_characterInfos) {
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
    if (m_characterInfos.size() == 0) {
        return;
    }
    
    float lastX=0;
    for (CharacterInfo* frame : m_characterInfos) {
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
    
    for (CharacterInfo* frame : m_characterInfos) {
        delete frame;
    }
    m_characterInfos.clear();
    for (int i=0;i!=m_text.size();++i) {
        CharacterInfo* frame = PaintEngine::GetInstance()->addText(m_text[i], m_fontName, m_fontSize);
        if (frame) {
            m_characterInfos.push_back(frame);
        }
    }
}

DE_END
