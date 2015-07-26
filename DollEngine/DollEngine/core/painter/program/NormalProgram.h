//
//  NormalProgram.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__NormalProgram__
#define __DollEngine__NormalProgram__

#include "GLProgram.h"

DE_BEGIN
class NormalProgram : public GLProgram
{
public:
    NormalProgram();
    ~NormalProgram();
    bool init();
    void actived(PaintConfig& config);
    
};
DE_END

#endif /* defined(__DollEngine__NormalProgram__) */
