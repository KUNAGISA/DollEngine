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
    
    bool begin(int w,int h,Image* bg=NULL);
    void end();
protected:
    DrawFBOId m_FBO;
    DrawFBOId m_oldFBO;
};

DE_END

#endif /* defined(__DollEngine__RTT__) */
