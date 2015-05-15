//
//  AutoReleasePool.h
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__AutoReleasePool__
#define __DollEngine__AutoReleasePool__

#include "Units.h"
#include "BaseComp.h"

DE_BEGIN

class AutoReleasePool
{
public:
    Shared(AutoReleasePool);
    void autoRelease();
    void addAutoRelease(BaseComp* comp);
    void removeAutoRelease(BaseComp* comp);
protected:
    set<BaseComp*> m_comps;
};

DE_END

#endif /* defined(__DollEngine__AutoReleasePool__) */
