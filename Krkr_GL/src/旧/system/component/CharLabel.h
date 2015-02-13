//
//  CharLabel.h
//  Krkr_GL
//
//  Created by ios开发－b on 14/12/27.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__CharLabel__
#define __Krkr_GL__CharLabel__

#include "COM.h"
#include "CharFrame.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "System.h"

class CharLabel : public COM
{
public:
    CharLabel();
    virtual ~CharLabel();
    void trigger();
    void refresh();
    PROPERTY_CONST(wstring, FontName, m_fontName){m_fontName=v;refresh();}
    PROPERTY_CONST(wstring, String, m_wstring){m_wstring=v;refresh();}
    PROPERTY(float, FontSize, m_fontSize){m_fontSize=v;refresh();}
    PROPERTY(float, X, m_x){m_x=v;System::GetInstance()->setTransChanged(true);}
    PROPERTY(float, Y, m_y){m_y=v;System::GetInstance()->setTransChanged(true);}
    PROPERTY(float, OffsetY, m_offsetY){m_offsetY=v;System::GetInstance()->setTransChanged(true);}
    PROPERTY_RO(float, Width, m_width);
    PROPERTY_RO(float, BearingY, m_bearingY);
    PROPERTY_RO(float, ImageHeight, m_imageHeight);
    PROPERTY(float, Bottom, m_bottom){m_bottom=v;}
public:
    PROPERTY(CharFrame*, Frame, m_frame);
    PROPERTY(CharFrame*, OutlineFrame, m_outlineFrame);
    PROPERTY(ShaderProgram*, Program, m_program){m_program=v;}
private:
    Transform* m_trans;
    Transform* m_worldTrans;
};


#endif /* defined(__Krkr_GL__CharLabel__) */
