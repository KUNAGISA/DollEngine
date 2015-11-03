//
//  NormalProgram.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__NormalProgram__
#define __DollEngine__NormalProgram__

#include "PaintProgram.h"

DE_BEGIN
class NormalProgram : public PaintProgram
{
public:
    NormalProgram();
    ~NormalProgram();
    void initShaderAttrib();
    void bind();
    void preparePaint(PaintConfig& config);
    void preparePaintWithScale9(PaintConfig& config);
    
};
DE_END

#endif /* defined(__DollEngine__NormalProgram__) */
