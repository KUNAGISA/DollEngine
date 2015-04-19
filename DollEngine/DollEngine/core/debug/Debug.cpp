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

static const int kMaxLogLen = 16*1024;
static char logbuff[sizeof(char) * (kMaxLogLen + 1)];
char* Debug::message(const char* format,...)
{
    va_list args;
    va_start(args, format);
    memset(logbuff, 0, sizeof(logbuff));
    vsprintf(logbuff, format, args);
    va_end(args);
    printf("%s\n", logbuff);
    
    return logbuff;
}

string Debug::throwMsg(DEBUG_MSG error,const string& p1)
{
    switch (error) {
        case ERROR_IMAGE_LOAD_FAILD:
            return message("图片资源加载失败:%s",p1.c_str());
            break;
        case ERROR_FILE_EXIST_FAILD:
            return message("文件未找到:%s",p1.c_str());
            break;
        default:
            return message("未知错误");
            break;
    }
}

DE_END
