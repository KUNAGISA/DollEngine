//
//  Debug.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Debug__
#define __DollEngine__Debug__

#include "CoreType.h"

DE_BEGIN

enum DEBUG_MSG
{
    ERROR_IMAGE_LOAD_FAILD = 1001,
    ERROR_FILE_EXIST_FAILD = 1002,
    ERROR_ADDFONT_FAILD = 1003,
    
    ERROR_OPENGL_ERROR = 4001,
};

class Debug
{
public:
    Debug();
    virtual ~Debug();
    
    static char* message(const char* format,...);
    static string throwMsg(DEBUG_MSG error,const string& p1="");
    static string throwMsg(const string& v){return v;}
};

DE_END

#endif /* defined(__DollEngine__Debug__) */
