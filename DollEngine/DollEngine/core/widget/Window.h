//
//  Window.h
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Window__
#define __DollEngine__Window__

#include "CoreUnits.h"

DE_BEGIN

class Window
{
public:
    Window();
    void initialize(float w,float h);
    
    
    PROPERTY(bool, Visible, m_visible){m_visible=v;}
protected:
    void* m_deviceWindow;
};

DE_END

#endif /* defined(__DollEngine__Window__) */
