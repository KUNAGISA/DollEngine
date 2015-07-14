//
//  Label.h
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Label__
#define __DollEngine__Label__

#include "Painter.h"
#include "Application.h"

DE_BEGIN

class TextFrame;

class Label : public Painter
{
public:
    Label();
    ~Label();
    
    virtual Size getPaintSize();
public:
    PROPERTY_CONST(string, FontName, m_fontName){
        if(m_fontName!=v){
            m_fontName=v;m_textChanged=true;
            NEED_REDRAW;
        }
    }
    PROPERTY(int, FontSize, m_fontSize){
        if(m_fontSize!=v){
            m_fontSize=v;m_textChanged=true;
            NEED_REDRAW;
        }
    }
    PROPERTY_CONST(string, Text, m_text){
        if(m_text!=v){
            m_text=v;m_textChanged=true;
            NEED_REDRAW;
        }
    }
public:
    void update();
    void updateText();
    
protected:
    bool m_textChanged;
    vector<TextFrame*> m_allTextFrames;
};

DE_END

#endif /* defined(__DollEngine__Label__) */
