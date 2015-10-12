//
//  JsonParser.h
//  DollEngine
//
//  Created by DollStudio on 15/7/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__JsonParser__
#define __DollEngine__JsonParser__

#include "CoreUnits.h"
#include "TjsBind.h"

DE_BEGIN

class JsonParser
{
public:
    enum JSON_TYPE
    {
        JSON_UNKNOW=0,
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_INT,
        JSON_DOUBLE,
        JSON_NULL
    };
    
    enum PARSETYPE
    {
        START = 0,
        END,
        WAITKEY,
        WAITVALUE,
    };
    Shared(JsonParser);
    tTJSVariant fromJsonFile(const String& path);
    tTJSVariant fromJsonString(const wchar_t* str);
private:
    wchar_t* arrayWithString(wchar_t* str,tTJSVariant& _out);
    wchar_t* dictWithString(wchar_t* str,tTJSVariant& _out);
    wchar_t* valueWithString(wchar_t* str,tTJSVariant& _out);
    wchar_t* stringWithString(wchar_t* str,String& _out);
    wchar_t* stringWithString(wchar_t* str,tTJSVariant& _out);
    wchar_t* nunberWithString(wchar_t* str,tTJSVariant& _out);
    wchar_t* emptyWithString(wchar_t* str);
};

DE_END

#endif /* defined(__DollEngine__JsonParser__) */
