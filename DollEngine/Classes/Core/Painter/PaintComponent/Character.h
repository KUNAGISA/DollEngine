//
//  Character.h
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Character__
#define __DollEngine__Character__

#include "Image.h"
#include "System.h"

DE_BEGIN

class CharacterInfo;

class Character : public Image
{
public:
    Character();
    ~Character();
    
    virtual void setSizeToImageSize();
    virtual void paint(Transform *trans);
public:
    PROPERTY_CONST(String, FontName, m_fontName){
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
    PROPERTY_CONST(String, Text, m_text){
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
    vector<CharacterInfo*> m_characterInfos;
};

DE_END

#endif /* defined(__DollEngine__Character__) */
