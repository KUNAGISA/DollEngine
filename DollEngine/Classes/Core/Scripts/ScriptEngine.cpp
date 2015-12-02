//
//  ScriptEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "ScriptEngine.h"
#include "TjsBind.h"
#include "TjsSystem.h"
#include "TjsStorages.h"
#include "TjsScripts.h"
#include "TjsConsole.h"
#include "TjsDictIterator.h"
#include "System.h"
#include "Storages.h"
#ifdef __QT__
#include "QtConsole.h"
#else
#include "Console.h"
#endif
DE_BEGIN

TJS_NATIVE_FUNCTION_BEGIN(TJSForeach)

if(numparams < 2) return TJS_E_BADPARAMCOUNT;

tTJSVariant* dict = param[0];
tTJSVariant* func = param[1];
if(dict == NULL || func == NULL || dict->AsObjectNoAddRef() == NULL || func->AsObjectNoAddRef() == NULL) {
    return TJS_E_INVALIDPARAM;
}

TjsDictIterator iter;
iter.begin(*dict);
while(iter.next()){
    iTJSDispatch2* incontext = func->AsObjectThisNoAddRef();
    iTJSDispatch2* f = func->AsObjectNoAddRef();
    tTJSInterCodeContext* func2 = dynamic_cast<tTJSInterCodeContext*>(f);
    if (func) {
        tTJSVariant v1 = iter.key();
        tTJSVariant v2 = iter.value();
        tTJSVariant* params[2] = {&v1,&v2};
        func2->FuncCall(0,NULL,NULL,NULL,2,params,incontext);
    }
}
return TJS_S_OK;
TJS_NATIVE_FUNCTION_END

void TJS_INTF_METHOD DE_TJSTextWriteStream::Write(const tTJSString & targ)
{
    str.append(targ.c_str());
}

void TJS_INTF_METHOD DE_TJSTextWriteStream::Destruct(){
    if(path.find(DE::System::GetInstance()->getSaveDataPath()) == String::npos) {
        path = System::GetInstance()->getSaveDataPath() + path;
    }
    str.saveToFile(path);
    delete this;
}

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
        TJS_REGIST_CLASS(System)
        TJS_REGIST_CLASS(Storages)
        TJS_REGIST_CLASS(Scripts)
        TJS_REGIST_CLASS(Console)
        
        TJS_REGIST_FUNCTION(TJSForeach, "foreach")
        
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
    TJS::eTJSError* e0 = (TJS::eTJSError*)error;
    TJS::eTJSScriptError* e1 = dynamic_cast<TJS::eTJSScriptError*>(e0);
    if(e1){
        ScriptEngine::Global()->OutputExceptionToConsole(e1->GetMessage().AsStdString().c_str());
        ScriptEngine::Global()->OutputExceptionToConsole(L"STACK:");
        String tra = e1->GetTrace().AsStdString();
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
    }
    else {
        ScriptEngine::Global()->OutputExceptionToConsole(e0->GetMessage().AsStdString().c_str());
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


DE_END
