//
//  GrowProgram.h
//  DollEngine
//
//  Created by DollStudio on 15/8/23.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GrowProgram__
#define __DollEngine__GrowProgram__

#include "NormalProgram.h"

DE_BEGIN
class GrowProgram : public NormalProgram
{
public:
    GrowProgram();
    ~GrowProgram();
    virtual bool bind();
    const char* getShader_F();
    virtual void actived(PaintConfig& config);
    
};
DE_END

#endif /* defined(__DollEngine__GrowProgram__) */
