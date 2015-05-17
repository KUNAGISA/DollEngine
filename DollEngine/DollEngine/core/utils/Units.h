//
//  Units.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Units__
#define __DollEngine__Units__

#include "CoreType.h"
#include "Debug.h"

DE_BEGIN

extern void GLCheckError();
extern string StringWithFormat(const char* format,...);
extern void Utf8ToUnicode(const char* src, wstring& target);
extern void Utf8ToVector(const string& _in, vector<string>& _out);

DE_END

#endif /* defined(__DollEngine__Units__) */
