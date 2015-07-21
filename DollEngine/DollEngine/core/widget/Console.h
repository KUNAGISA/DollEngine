//
//  Console.h
//  DollEngine
//
//  Created by DollStudio on 15/4/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Console__
#define __DollEngine__Console__

#include "CoreUnits.h"

DE_BEGIN

class Console
{
public:
    Shared(Console)
    PROPERTY(bool, Visible, m_visible);
};

DE_END

#endif /* defined(__DollEngine__Console__) */
