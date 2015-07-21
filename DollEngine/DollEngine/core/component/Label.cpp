//
//  Label.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Label.h"
#include "GLCache.h"
#include "TextFrame.h"
#include "GameObject.h"
#include "GLPainter.h"
#include "GLCanvas.h"

DE_BEGIN

Label::Label()
:m_textChanged(false)
,m_fontSize(DEFFONTSIZE)
,m_fontName(DEFFONT)
,m_text("")
{
    setCompName("Painter");
}

Label::~Label()
{
    for (TextFrame* frame : m_allTextFrames) {
        SAFF_RELEASE(frame);
    }
    m_allTextFrames.clear();
}


Size Label::getPaintSize()
{
    if (m_allTextFrames.size() > 0) {
        float h = m_fontSize;
        float w = 0;
        for (TextFrame* frame : m_allTextFrames) {
            w += frame->getFont()->advance;
        }
        return Size(w,h);
    }
    else {
        return Size::Zero();
    }
}

void Label::update()
{
    updateText();
    blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    
    if (getObject()) {
        m_transform->copy(getObject()->getTransInWorld());
    }
    else {
        m_transform->copy(GLCanvas::GetInstance()->getGlobalTrans());
    }
    float lastX=0;
    for (TextFrame* frame : m_allTextFrames) {
        Transform orgin;
        orgin.copy(m_transform);
        Transform offst;
        offst.setX(lastX);
        offst.setY(m_fontSize-frame->getFont()->bearingY);
        offst.flush();
        orgin.setWidth(frame->getWidth());
        orgin.setHeight(frame->getHeight());
        orgin.transform(&offst);
        
        GLPainter::GetInstance()->paint(frame, &orgin, &m_color, m_program);
        lastX += frame->getFont()->advance;
    }
}

void Label::updateText()
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
