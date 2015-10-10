//
//  ScriptEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "ScriptEngine.h"
#include "TjsBind.h"
//#include "TjsSystem.h"
//#include "TjsStorages.h"
//#include "TjsScripts.h"
//#include "TjsUnits.h"
#include "Debug.h"
#include "System.h"
#include "TjsConsole.h"

DE_BEGIN

static const int kMaxLogLen = 32*1024;
static char logbuff[sizeof(char) * (kMaxLogLen + 1)];
void Debug::message(const char* format,...)
{
    va_list args;
    memset(logbuff, 0, sizeof(logbuff));
    va_start(args, format);
    vsprintf(logbuff, format, args);
    va_end(args);
    String str = logbuff;
    ScriptEngine::Global()->OutputToConsole(str.c_str());
}

void Debug::throwMsg(DEBUG_MSG error,const String& p1)
{
    String msg;
    switch (error) {
        case ERROR_IMAGE_LOAD_FAILD:
            msg = L"图片资源加载失败:"+p1;
            break;
        case ERROR_FILE_EXIST_FAILD:
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

void Debug::throwMsg(DEBUG_MSG error,int p1,const String& p2)
{
    String msg;
    switch (error) {
        case ERROR_KAG_UNKONW:
            msg = UnicodeWithFormat(L"(#%d)KAG解析发生未知错误",p1);
            break;
        case ERROR_KAG_LABELKEY_NULL:
            msg = UnicodeWithFormat(L"(#%d)标签的名字不能为空",p1);
            break;
        case ERROR_KAG_VALUE_STRING_ENDED:
            msg = UnicodeWithFormat(L"(#%d)字符串没有结尾，可能缺少 \" 或 \' ，请检查",p1);
            break;
        case ERROR_KAG_TAG_ENDED:
            msg = UnicodeWithFormat(L"(#%d)Tag没有结尾，可能缺少 ] ，请检查",p1);
            break;
        case ERROR_KAG_LABEL_FIND_FAIL:
            msg = UnicodeWithFormat(L"(#%d)未找到名为%ls的标签",p1,p2.c_str());
            break;
        case ERROR_KAG_TAG_FIND_FAIL:
            msg = UnicodeWithFormat(L"(#%d)未找到名为%ls的指令",p1);
            break;
        case ERROR_KAG_TOO_MANY_RETURN:
            msg = UnicodeWithFormat(L"(#%d)过多的Return指令，与Call指令无法形成对应",p1);
            break;
        case ERROR_KAG_MACRONAME_EMPTY:
            msg = UnicodeWithFormat(L"(#%d)Macro的name属性为空",p1);
            break;
        case ERROR_KAG_MACRO_NESTING:
            msg = UnicodeWithFormat(L"(#%d)Macro不可嵌套",p1);
            break;
        case ERROR_KAG_IF_FAIL:
            msg = UnicodeWithFormat(L"(#%d)if、elsif、else、endif不对应",p1);
            break;
        default:
            msg = UnicodeWithFormat(L"(#%d)KAG发生未知错误",p1);
            break;
    }
    TJS_eTJSError(msg);
}

void Debug::throwMsg(const String& v)
{
    TJS_eTJSError(v);
}

static TJS::tTJS* s_tjs = null;

TJS::tTJS* ScriptEngine::Global()
{
    return s_tjs;
}

ScriptEngine::ScriptEngine()
{
    if (!s_tjs)
    {
        s_tjs = new tTJS();
        TJSEnableDebugMode=true;
        tTJSVariant val;
        iTJSDispatch2 *dsp;
        iTJSDispatch2* global = s_tjs->GetGlobalNoAddRef () ;
//        TJS_REGIST_CLASS(System)
//        TJS_REGIST_CLASS(Storages)
//        TJS_REGIST_CLASS(Scripts)
//        TJS_REGIST_CLASS(Units)
        
        
        TVPLoadMessage();
        //        REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
        
        // AutoRegisterで登録されたクラス等を登録する
        ncbAutoRegister::AllRegist();
        
        s_tjs->SetConsoleOutput(TjsConsole::GetInstance());
    }
}

void ScriptEngine::catchError(void* error)
{
    TJS::eTJSScriptError& e = *(TJS::eTJSScriptError*)error;
    ScriptEngine::Global()->OutputExceptionToConsole(L"STACK:");
    String tra = e.GetTrace().AsStdString();
    size_t idx = tra.find(L"(");
    while (idx!=String::npos) {
        size_t idx2 = tra.find(L" <-- anonymous@",idx);
        String sub = tra.substr(idx,idx2-idx);
        ScriptEngine::Global()->OutputExceptionToConsole(sub.c_str());
        if (idx2 == String::npos) {
            break;
        }
        idx = tra.find(L"(",idx2);
    }
    System::GetInstance()->setIsError(true);
}

bool ScriptEngine::eval(const String& code,void* ret)
{
    if (code.size() == 0) {
        return false;
    }
    try {
        s_tjs->EvalExpression( code,(tTJSVariant*)ret, NULL,NULL ) ;
        return true;
    }
    TJS_CATCH
    return false;
}

bool ScriptEngine::exec(const String& code,void* ret)
{
    if (code.size() == 0) {
        return false;
    }
    try {
        s_tjs->ExecScript ( code,(tTJSVariant*)ret, NULL,NULL ) ;
        return true;
    }
    TJS_CATCH
    return false;
}

void ScriptEngine::doAsyncFunctions()
{
    if (m_allAsyncFunctions.size() == 0) {
        return;
    }
    vector<AsyncFunction> tmp = m_allAsyncFunctions;
    std::sort(tmp.begin(), tmp.end(),
              [](const AsyncFunction& a, const AsyncFunction& b){
                  return a.priority < b.priority;
              });
    m_allAsyncFunctions.clear();
    
    try {
        for (auto iter = tmp.begin();
             iter != tmp.end(); ++iter)
        {
            AsyncFunction& t = *iter;
            t.handler->FuncCall(0, NULL, NULL, NULL, 0, NULL, t.objthis);
            t.handler->Release();
            if (t.objthis) {
                t.objthis->Release();
            }
        }
    }TJS_CATCH
}

void ScriptEngine::addAsyncFunction(const AsyncFunction& func)
{
    func.handler->AddRef();
    if (func.objthis) {
        func.objthis->AddRef();
    }
    m_allAsyncFunctions.push_back(func);
}

void ScriptEngine::print(const String& text)
{
    s_tjs->GetConsoleOutput()->Print(text.c_str());
}

void ScriptEngine::setConsoleVisible(bool v)
{
    TjsConsole::GetInstance()->setVisible(v);
}

bool ScriptEngine::getConsoleVisible()
{
    return TjsConsole::GetInstance()->getVisible();
}

DE_END
