//
//  Debug.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Debug.h"

DE_BEGIN
Debug::Debug()
{
    
}

Debug::~Debug()
{
    
}

static const int kMaxLogLen = 32*1024;
static char logbuff[sizeof(char) * (kMaxLogLen + 1)];
void Debug::message(const char* format,...)
{
//    va_list args;
//    va_start(args, format);
//    printf(format,args);
//    va_end(args);
//    printf("\n");
    va_list args;
    memset(logbuff, 0, sizeof(logbuff));
    va_start(args, format);
    vsprintf(logbuff, format, args);
    va_end(args);
    printf("%s\n", logbuff);
//
//    return logbuff;
}



DE_END
