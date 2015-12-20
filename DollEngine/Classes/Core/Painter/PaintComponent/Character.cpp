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
,m_fontName(L"")
,m_text("")
{
    m_info = new ImageInfo();
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
    if (m_characterInfos.size() > 0) {
        float w = 0;
        float h = 0;
        for (CharacterInfo* frame : m_characterInfos) {
            w += frame->getFont()->advance;
            h = max(h,(float)frame->getPaintHeight()-frame->getFont()->yMin);
        }
        setPaintSize(w,h);
    }
    else {
        setPaintSize(0,0);
    }
}

void Character::paint(Transform* trans)
{
    if(m_textChanged) {
        setSizeToImageSize();
    }
    if (m_characterInfos.size() == 0) {
        return;
    }
    
    float lastX=0;
    for (CharacterInfo* frame : m_characterInfos) {
        FontData* font = frame->getFont();
        frame->setColor(m_startColor,m_endColor,m_startOpacity,m_endOpacity);
        Transform orgin;
        if(trans) {
            orgin.assign(trans);
        }
        
        Transform offst;
        offst.setX(lastX + font->bearingX);
        float y = (frame->getPaintHeight()-font->bearingY);
        offst.setY(y);
        offst.setAnchorX(0);
        offst.setAnchorY(0);
        offst.flush();
        orgin.transform(&offst);
        orgin.setWidth(frame->getPaintWidth());
        orgin.setHeight(frame->getPaintHeight());
        PaintConfig config;
        flushPaintConfig(config);
        config.trans = &orgin;
        config.info = frame;
//        config.width = frame->getWidth();
//        config.height = frame->getHeight();
        PaintEngine::GetInstance()->preparePaint(config);
        lastX += font->advance;
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
        String t = m_text.substr(i,1);
        CharacterInfo* frame = PaintEngine::GetInstance()->addText(t, m_fontName, m_fontSize);
        if (frame) {
            m_characterInfos.push_back(frame);
        }
    }
}

DE_END
