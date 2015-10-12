//
//  TjsSet.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/9.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsSet.h"



NCB_REGISTER_CLASS_DIFFER(Set,TjsSet)
{
    TJS_FACTORY
    NCB_METHOD(add);
    NCB_METHOD(remove);
#ifdef __QT__
    NCB_METHOD_DIFFER(foreach,toForeach);
#else
    NCB_METHOD(foreach);
#endif
    NCB_METHOD(clear);
    NCB_METHOD(assign);
    NCB_PROPERTY_RO(count, count);
}