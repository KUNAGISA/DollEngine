//
//  RTT.h
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__RTT__
#define __DollEngine__RTT__

#include "Painter.h"

DE_BEGIN

class RTT:public Painter
{
public:
    RTT();
    ~RTT();
    
    bool loadRender(GameObject* obj, int w,int h,Painter* bg=null);
protected:
    GLuint m_FBO;
    GLint m_oldFBO;
};

DE_END

#endif /* defined(__DollEngine__RTT__) */
