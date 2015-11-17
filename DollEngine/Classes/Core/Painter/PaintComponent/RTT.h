//
//  RTT.h
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__RTT__
#define __DollEngine__RTT__

#include "Image.h"

DE_BEGIN

class RTT:public Image
{
public:
    RTT();
    ~RTT();
    
    bool begin(int w,int h);
    virtual void paint(Transform* trans);
    void end();
    
    void setOpacity(int v){m_startOpacity=m_endOpacity=v;NEED_REDRAW}
    int getOpacity(){return m_startOpacity;}
protected:
    DrawFBOId m_FBO;
    DrawOldFBOId m_oldFBO;
};

DE_END

#endif /* defined(__DollEngine__RTT__) */
