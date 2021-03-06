//
//  Console.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/12.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Console.h"
#include "ScriptEngine.h"
#include "TjsBind.h"

DE_BEGIN

DE::Console* DE::Console::Instance = NULL;

void Console::assertMsg(void* v,const String& msg)
{
    if(v == 0){
        if(msg.empty()){
            throwMsg(L"未知断言");
        }
        else {
            throwMsg(msg);
        }
    }
}

void Console::log(const String& text)
{
    if(text.length() == 0) return;
    ScriptEngine::Global()->OutputToConsole(text.c_wstr());
}

void Console::throwMsg(const String& v)
{
    TJS_eTJSError(v);
}

void Console::throwMsg(DEBUG_MSG error,const String& p1)
{
    String msg;
    switch (error) {
        case ERROR_IMAGE_LOAD_FAILD:
            msg = L"图片资源加载失败:"+p1;
            break;
        case ERROR_FILE_NOT_EXIST:
            msg = L"文件未找到:"+p1;
            break;
        case ERROR_ADDFONT_FAILD:
            msg = L"添加字体时出错";
            break;
        default:
            msg = L"未知错误";
            break;
    }
    TJS_eTJSError(msg);
}

void Console::throwMsg(DEBUG_MSG error,int p1,const String& p2)
{
    String msg;
    switch (error) {
        case ERROR_KAG_UNKONW:
            msg = String::fromFormat(L"(#%d)KAG解析发生未知错误",p1);
            break;
        case ERROR_KAG_LABELKEY_NULL:
            msg = String::fromFormat(L"(#%d)标签的名字不能为空",p1);
            break;
        case ERROR_KAG_VALUE_STRING_ENDED:
            msg = String::fromFormat(L"(#%d)字符串没有结尾，可能缺少 \" 或 \' ，请检查",p1);
            break;
        case ERROR_KAG_TAG_ENDED:
            msg = String::fromFormat(L"(#%d)Tag没有结尾，可能缺少 ] ，请检查",p1);
            break;
        case ERROR_KAG_LABEL_FIND_FAIL:
            msg = String::fromFormat(L"(#%d)未找到名为%ls的标签",p1,p2.c_wstr());
            break;
        case ERROR_KAG_TAG_FIND_FAIL:
            msg = String::fromFormat(L"(#%d)未找到名为%ls的指令",p1);
            break;
        case ERROR_KAG_TOO_MANY_RETURN:
            msg = String::fromFormat(L"(#%d)过多的Return指令，与Call指令无法形成对应",p1);
            break;
        case ERROR_KAG_MACRONAME_EMPTY:
            msg = String::fromFormat(L"(#%d)Macro的name属性为空",p1);
            break;
        case ERROR_KAG_MACRO_NESTING:
            msg = String::fromFormat(L"(#%d)Macro不可嵌套",p1);
            break;
        case ERROR_KAG_IF_FAIL:
            msg = String::fromFormat(L"(#%d)if、elsif、else、endif不对应",p1);
            break;
        default:
            msg = String::fromFormat(L"(#%d)KAG发生未知错误",p1);
            break;
    }
    TJS_eTJSError(msg);
}

void Console::evalScripts(const String& v)
{
    try {
        tTJSVariant ret;
        Print(v.c_wstr());
        ScriptEngine::GetInstance()->eval(v,&ret);
        ret.ToString();
        const tjs_char* data = ret.AsStringNoAddRef()->operator const tjs_char *();
        if(data == NULL) {
            Print(L"(void)");
        }
        else {
            Print(data);
        }
    }
    TJS_CATCH
}

DE_END
