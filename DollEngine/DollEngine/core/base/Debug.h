//
//  Debug.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Debug__
#define __DollEngine__Debug__

#include "Types.h"

DE_BEGIN

enum DEBUG_MSG
{
    ERROR_NONE = 0,
    
    ERROR_IMAGE_LOAD_FAILD = 1001,
    ERROR_FILE_EXIST_FAILD = 1002,
    ERROR_ADDFONT_FAILD = 1003,
    
    ERROR_OPENGL_ERROR = 4001,
    
    ERROR_KAG_UNKONW = 6000,
    ERROR_KAG_LABELKEY_NULL,
    ERROR_KAG_VALUE_STRING_ENDED,
    ERROR_KAG_TAG_ENDED,
    ERROR_KAG_LABEL_FIND_FAIL,
    ERROR_KAG_TAG_FIND_FAIL,
    ERROR_KAG_TOO_MANY_RETURN,
    ERROR_KAG_MACRONAME_EMPTY,
    ERROR_KAG_MACRO_NESTING,
    ERROR_KAG_IF_FAIL,
};

class Debug
{
public:
    Debug();
    virtual ~Debug();
    
    static void message(const char* format,...);
    static void throwMsg(DEBUG_MSG error,const string& p1="");
    static void throwMsg(DEBUG_MSG error,int p1,const wstring& p2=L"");
    static void throwMsg(const string& v);
};

DE_END

#endif /* defined(__DollEngine__Debug__) */
