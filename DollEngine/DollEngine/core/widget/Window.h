//
//  Window.h
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Window__
#define __DollEngine__Window__

#include "CoreTypes.h"

DE_BEGIN

class RTT;
class Painter;

class Window
{
public:
    Window();
    virtual ~Window();
    static Window* GetInstance();
    virtual void setSize(int w,int h){m_width=w,m_height=h;}
    
    PROPERTY(bool, Visible, m_visible){m_visible=v;}
    PROPERTY(bool, FullScreen, m_fullScreen){m_fullScreen=v;}
    PROPERTY_CONST(String, Title, m_title){m_title=v;}
    
    PROPERTY(int,Width,m_width){m_width=v;}
    PROPERTY(int,Height,m_height){m_height=v;}
protected:
};

DE_END

#endif /* defined(__DollEngine__Window__) */
