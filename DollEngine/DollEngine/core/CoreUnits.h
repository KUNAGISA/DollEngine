//
//  Units.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Units__
#define __DollEngine__Units__

#include "CoreTypes.h"
#include "Debug.h"
#include "Status.h"
#include "DrawInterface.h"

DE_BEGIN

class GLProgram;

extern void GLCheckError();
extern void GLCheckProgramError(GLProgram*);
extern string Utf8WithFormat(const char* format,...);
extern wstring UnicodeWithFormat(const wchar_t* format,...);
extern void UnicodeToUtf8(const wchar_t* src, string& target);
extern void Utf8ToVector(const String& _in, vector<string>& _out);
extern unsigned char* WCharToChar(int& src, unsigned char*target);
extern void CharToWChar(const char* src,wchar_t* target);
extern int64_t GetMilliSeconds();
extern double GetSeconds();

DE_END

#endif /* defined(__DollEngine__Units__) */
