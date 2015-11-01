//
//  TjsConsole.h
//  DollEngine
//
//  Created by DollStudio on 15/7/25.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsConsole__
#define __DollEngine__TjsConsole__

#include "CoreUnits.h"
#include "tjs.h"

using namespace TJS;

DE_BEGIN

class TjsConsole :public iTJSConsoleOutput
{
public:
    Shared(TjsConsole)
    PROPERTY(bool, Visible, m_visible);
    virtual void ExceptionPrint(const tjs_char *msg);
    virtual void Print(const tjs_char *msg);
};

DE_END

#endif /* defined(__DollEngine__TjsConsole__) */
