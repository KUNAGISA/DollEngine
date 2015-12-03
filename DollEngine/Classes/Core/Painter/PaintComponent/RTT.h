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
    
    void init(int w,int h);
    bool begin(float r,float g,float b,float a);
    virtual void paint(Transform* trans);
    void end();
    
    virtual bool saveToFile(const String& path,int w=0, int h=0);
    
    void setOpacity(int v){m_startOpacity=m_endOpacity=v;NEED_REDRAW}
    int getOpacity(){return m_startOpacity;}
protected:
    DrawFBOId m_FBO;
    DrawOldFBOId m_oldFBO;
};

DE_END

#endif /* defined(__DollEngine__RTT__) */
