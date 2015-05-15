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
    for (TextFrame* frame : m_allFrames) {
        SAFF_RELEASE(frame);
    }
    m_allFrames.clear();
}

void Label::update()
{
    if (m_textChanged) {
        m_textChanged=false;
        updateText();
    }
    blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    
    if (getObject()) {
        m_transform->copy(getObject()->getTransInWorld());
    }
    else {
        m_transform->copy(GLCanvas::GetInstance()->getGlobalTrans());
    }
    float lastX=0;
    for (TextFrame* frame : m_allFrames) {
        Transform orgin;
        orgin.copy(m_transform);
        Transform offst;
        offst.setX(lastX);
        offst.setY(m_fontSize-frame->getBearingY());
        offst.flush();
        orgin.setWidth(frame->getWidth());
        orgin.setHeight(frame->getHeight());
        orgin.transform(&offst);
        
        GLCanvas::GetInstance()->paint(frame, &orgin, &m_color, m_program);
        lastX += frame->getAdvance();
    }
}

void Label::updateText()
{
    for (TextFrame* frame : m_allFrames) {
        SAFF_RELEASE(frame);
    }
    m_allFrames.clear();
    vector<string> strs;
    Utf8ToVector(m_text,strs);
    for (auto iter = strs.begin();
         iter != strs.end(); ++iter) {
        TextFrame* frame = GLCache::GetInstance()->addText(*iter, m_fontName, m_fontSize);
        if (frame) {
            frame->retain();
            m_allFrames.push_back(frame);
        }
    }
    
}

DE_END
