//
//  de-debug.h
//  DollEngine
//
//  Created by DollStudio on 15/2/21.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_debug__
#define __DollEngine__de_debug__

#include "de-functions.h"


enum E_ID
{
    E_UNKNOW=0,
    E_STORAGE_FILE_NOT_FIND,
    E_STORAGE_FILE_NOT_OPEN,
};

NAMESPACE_DE_DEBUG

extern void message(const char* format,...);
extern void e_throw(const char* format,...);
extern void e_message(E_ID,...);

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_debug__) */
