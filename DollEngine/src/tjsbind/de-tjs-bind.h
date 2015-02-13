//
//  de-tjs-bind.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_tjs_bind__
#define __DollEngine__de_tjs_bind__

#include "de.h"
#include "ncbind.hpp"

class deTJSClass
{
public:
    deTJSClass();
    virtual ~deTJSClass();
    tTJSCustomObject* _self;
};


#endif /* defined(__DollEngine__de_tjs_bind__) */
