//
//  Functions.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/6.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Functions.h"

static const int kMaxLogLen = 16*1024;
static char logbuff[sizeof(char) * (kMaxLogLen + 1)];
void debug_message(const char * pszFormat, ...)
{
    va_list args;
    va_start(args, pszFormat);
    memset(logbuff, 0, sizeof(logbuff));
    vsnprintf(logbuff, kMaxLogLen, pszFormat, args);
    va_end(args);
    printf("%s\n", logbuff);
    push_msg(logbuff);
    push_msg("\n");
}

void error_message(ERROR_INFOS infotype,...)
{
    const char* pszFormat = get_error_infos(infotype);
    va_list args;
    va_start(args, infotype);
    memset(logbuff, 0, sizeof(logbuff));
    vsnprintf(logbuff, kMaxLogLen, pszFormat, args);
    va_end(args);
    printf("%s\n", logbuff);
    push_msg(logbuff);
    push_msg("\n");
}


double get_utc_time()
{
    static timeval time_t;
    gettimeofday(&time_t,0);
    return (double)time_t.tv_sec + (double)time_t.tv_usec/1000000.0f;
}

long long get_tick_count()
{
    static timeval time_t;
    gettimeofday(&time_t,0);
    static long long time_sec;
    time_sec = time_t.tv_sec;
    return time_sec*1000+time_t.tv_usec/1000;
}

static GLint s_gl_error_enum =0;
void check_opengl_error()
{
    s_gl_error_enum = glGetError();
    if(s_gl_error_enum!=0)
        EM(ERROR_OPENGL_UNKNOW,s_gl_error_enum);
}


uint uint_with_color4(const Vector4F& v)
{
    GLubyte r = v.r*255;
    GLubyte g = v.g*255;
    GLubyte b = v.b*255;
    GLubyte a = v.a*255;
    uint value = ((uint)r<<24) + ((uint)g<<16) + ((uint)b<<8) + a;
    return value;
}

Vector4F color4_with_uint(uint v)
{
    Vector4F color;
    color.r = (v>>24)/255.0f;
    color.g = (v>>16)/255.0f;
    color.b = (v>>8)/255.0f;
    color.a = (v>>0)/255.0f;
    return color;
}
