//
//  Status.h
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Status__
#define __DollEngine__Status__

#include "CoreTypes.h"

DE_BEGIN

class Status
{
public:
    Status():
    needRedraw(false),
    needSortTouches(false)
    {}
    Shared(Status)
    bool needRedraw;
    bool needSortTouches;
};

DE_END

#endif /* defined(__DollEngine__Status__) */
