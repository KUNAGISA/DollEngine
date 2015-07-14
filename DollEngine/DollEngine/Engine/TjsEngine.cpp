//
//  TjsEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsEngine.h"
#include "TjsBind.h"
#include "TjsSystem.h"
#include "TjsStorage.h"
#include "TjsScript.h"

DE_BEGIN
static TJS::tTJS* s_tjs = null;

TJS::tTJS* TjsEngine::Global()
{
    return s_tjs;
}

TjsEngine::TjsEngine()
{
    if (!s_tjs)
    {
        s_tjs = new tTJS();
        
        tTJSVariant val;
        iTJSDispatch2 *dsp;
        iTJSDispatch2* global = s_tjs->GetGlobalNoAddRef () ;
        TJS_REGIST_CLASS(System)
        TJS_REGIST_CLASS(Storages)
        TJS_REGIST_CLASS(Scripts)
        
        TVPLoadMessage();
        //        REGIST_TJS_FUNCTION(TJSPrint,"print")
        //        REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
        
        // AutoRegisterで登録されたクラス等を登録する
        ncbAutoRegister::AllRegist();
        
    }
}

bool TjsEngine::eval(const wstring& code,void* ret)
{
    
    return true;
}

bool TjsEngine::exec(const wstring& code,void* ret)
{
    return true;
}

DE_END