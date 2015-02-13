//
//  de-functions.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_functions__
#define __DollEngine__de_functions__

#include "de-types.h"

NAMESPACE_DE_BEGIN

DE_EXTERN void convert_utf8_to_wchar(const string& ch_in, wchar_t& ch_out);
DE_EXTERN void convert_utf8_to_wstring(const char* ch_in, wstring& ch_out);
DE_EXTERN void convert_wstring_to_string(const wstring& src, string& target);
DE_EXTERN unsigned char* convert_wchar_to_char(int& unic, unsigned char* pOutput);

NAMESPACE_DE_END

#endif /* defined(__DollEngine__de_functions__) */
