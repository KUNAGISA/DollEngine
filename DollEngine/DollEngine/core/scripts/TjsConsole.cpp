//
//  TjsConsole.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/25.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsConsole.h"

DE_BEGIN

#ifdef OS_IOS

void TjsConsole::setVisible(bool v)
{
    m_visible=v;
}

void TjsConsole::ExceptionPrint(const tjs_char *msg)
{
    Print(msg);
}

void TjsConsole::Print(const tjs_char *msg)
{
    printf("%ls",msg);
}

#endif


DE_END
