//
//  Console.h
//  DollEngine
//
//  Created by DollStudio on 15/7/25.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Console__
#define __DollEngine__Console__

#include "CoreUnits.h"
#include "tjs.h"

using namespace TJS;

DE_BEGIN

class Console :public iTJSConsoleOutput
{
public:
    static Console* Instance;
    static Console* GetInstance(){
        return Console::Instance;
    }
    virtual void setVisible(bool v){}
    virtual bool getVisible(){return false;}
    virtual void ExceptionPrint(const tjs_char *msg){Print(msg);}
    virtual void Print(const tjs_char *msg){
        printf("%s\n",String(msg).c_nstr());
    }
};

DE_END

#endif /* defined(__DollEngine__Console__) */
