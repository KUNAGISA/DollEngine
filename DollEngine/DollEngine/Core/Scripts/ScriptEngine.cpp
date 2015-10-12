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
#include "System.h"
#ifdef __QT__
#include "QtConsole.h"
#else
#include "Console.h"
#endif
DE_BEGIN

static TJS::tTJS* s_tjs = NULL;

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
        
        Console* console;
#ifdef __QT__
        console = (Console*)(new QtConsole());
#else
        console = new Console();
#endif
        s_tjs->SetConsoleOutput(console);
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

void ScriptEngine::log(const String& text)
{
    s_tjs->OutputToConsole(text.c_str());
}

void ScriptEngine::throwMsg(const String& v)
{
    s_tjs->OutputExceptionToConsole(v.c_str());
    TJS_eTJSError(v);
}

void ScriptEngine::throwMsg(DEBUG_MSG error,const String& p1)
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

void ScriptEngine::throwMsg(DEBUG_MSG error,int p1,const String& p2)
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
            msg = String::fromFormat(L"(#%d)未找到名为%ls的标签",p1,p2.c_str());
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

void ScriptEngine::setConsoleVisible(bool v)
{
    Console::GetInstance()->setVisible(v);
}

bool ScriptEngine::getConsoleVisible()
{
    return Console::GetInstance()->getVisible();
}

DE_END
