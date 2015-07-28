//
//  TjsConsole-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/25.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ConsoleController.h"
#include "TjsConsole.h"

DE_BEGIN

void TjsConsole::setVisible(bool v)
{
    m_visible=v;
    [[ConsoleController GetInstance] setVisible:v];
}

void TjsConsole::ExceptionPrint(const tjs_char *msg)
{
    string dt;
    UnicodeToUtf8(msg, dt);
    printf("【ERROR】%s\n",dt.c_str());
    NSString* str = [NSString stringWithUTF8String:dt.c_str()];
    NSString* dbg = [NSString stringWithFormat:@"【ERROR】%@",str];
    [[ConsoleController GetInstance]pushString:dbg];
}

void TjsConsole::Print(const tjs_char *msg)
{
    string dt;
    UnicodeToUtf8(msg, dt);
    printf("%s\n",dt.c_str());
    [[ConsoleController GetInstance]pushString:[NSString stringWithUTF8String:dt.c_str()]];
}

DE_END