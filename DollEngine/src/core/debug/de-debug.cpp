//
//  de-debug.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/21.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-debug.h"


NAMESPACE_DE_DEBUG

static map<E_ID, string> s_all_throw_log;

static const int s_msg_max_len = 16*1024;
static char s_msg_buffer[sizeof(char) * (s_msg_max_len + 1)];

void message(const char* format,...)
{
    va_list args;
    va_start(args, format);
    memset(s_msg_buffer, 0, sizeof(s_msg_buffer));
    vsnprintf(s_msg_buffer, s_msg_max_len, format, args);
    va_end(args);
    printf("%s\n", s_msg_buffer);
//    push_msg(s_msg_buffer);
//    push_msg("\n");
}

void e_throw(const char* format,...)
{
    va_list args;
    va_start(args, format);
    memset(s_msg_buffer, 0, sizeof(s_msg_buffer));
    vsnprintf(s_msg_buffer, s_msg_max_len, format, args);
    va_end(args);
    printf("%s\n", s_msg_buffer);
    
}

void e_message(E_ID em,...)
{
    if (s_all_throw_log.size() == 0)
    {
        s_all_throw_log[E_STORAGE_FILE_NOT_FIND]
        = "文件%ls未找到";
        
        s_all_throw_log[E_STORAGE_FILE_NOT_OPEN]
        = "文件%ls未打开";
    }
    va_list args;
    va_start(args, em);
    memset(s_msg_buffer, 0, sizeof(s_msg_buffer));
    vsnprintf(s_msg_buffer, s_msg_max_len, s_all_throw_log[em].c_str(), args);
    va_end(args);
    printf("%s\n", s_msg_buffer);
}

NAMESPACE_DE_END2
