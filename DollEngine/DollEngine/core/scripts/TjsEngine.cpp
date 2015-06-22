//
//  TjsEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsEngine.h"
#include "tjs.h"
#include "ncbind.hpp"

DE_BEGIN
static tTJS* s_tjs = null;

TjsEngine::TjsEngine()
{
    if (!s_tjs)
    {
        s_tjs = new tTJS();
        
        tTJSVariant val;
        iTJSDispatch2 *dsp;
        iTJSDispatch2* global = s_tjs->GetGlobalNoAddRef () ;
//        TJS_REGIST_CLASS(System)
//        TJS_REGIST_CLASS(Storages)
//        TJS_REGIST_CLASS(Scripts)
        
        TVPLoadMessage();
        //        REGIST_TJS_FUNCTION(TJSPrint,"print")
        //        REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
        
        // AutoRegisterで登録されたクラス等を登録する
        ncbAutoRegister::AllRegist();
        
    }
}

bool TjsEngine::eval(const string& code)
{
    
    return true;
}

bool TjsEngine::evalStorage(const string& filePath)
{
    return true;
}

bool TjsEngine::exec(const string& code)
{
    return true;
}

bool TjsEngine::execStorage(const string& filePath)
{
    return true;
}

DE_END