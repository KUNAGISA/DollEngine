//
//  Console.h
//  DollEngine
//
//  Created by DollStudio on 15/7/25.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Console__
#define __DollEngine__Console__

#include "CoreTypes.h"
#include "tjs.h"

using namespace TJS;

DE_BEGIN

enum DEBUG_MSG
{
    ERROR_NONE = 0,
    
    ERROR_IMAGE_LOAD_FAILD = 1001,
    ERROR_FILE_NOT_EXIST = 1002,
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

class Console :public iTJSConsoleOutput
{
public:
    static Console* Instance;
    static Console* GetInstance(){
        return Console::Instance;
    }
    Console(){Console::Instance = this;}
    void assertMsg(void* v,const String& msg);
    void log(const String& text);
    void throwMsg(const String& v);
    void throwMsg(DEBUG_MSG msg,const String& v1);
    void throwMsg(DEBUG_MSG msg,int v1,const String& v2);
    virtual void ExceptionPrint(const tjs_char *msg){Print(msg);}
    virtual void Print(const tjs_char *msg){
        printf("%s\n",String(msg).c_nstr());
    }
    void evalScripts(const String& v);
    virtual void setVisible(bool v){}
    virtual bool getVisible(){return false;}
};

DE_END

#endif /* defined(__DollEngine__Console__) */
