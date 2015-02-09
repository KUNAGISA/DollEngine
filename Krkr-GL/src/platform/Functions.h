//
//  Functions.h
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Functions__
#define __DollEngine__Functions__

#include "Macros.h"
#include "Types.h"
#include "ErrorInfos.h"
#include "ccGLStateCache.h"

class Image;
extern Image* get_image_data(const wstring& fullpath);
extern const wstring& get_app_path();
extern const wstring& get_document_path();
extern const wstring& get_cache_path();
extern void debug_message(const char* format,...);
extern void push_msg(const char* text);
extern void error_message(ERROR_INFOS infotype,...);
extern double get_utc_time();
extern long long get_tick_count();
extern void check_opengl_error();
extern float get_winframe_height();
extern float get_winframe_width();
extern uint uint_with_color4(const Vector4F& v);
extern Vector4F color4_with_uint(uint v);

#endif /* defined(__DollEngine__Functions__) */
