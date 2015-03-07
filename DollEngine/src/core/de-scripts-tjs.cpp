//
//  de-scripts-tjs.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/14.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "tjs.h"
#include "ncbind.hpp"
#include "tjsNative.h"
#include "tjsError.h"
#include "tjsString.h"
#include "tjsVariant.h"
#include "tjsDebug.h"
#include "tjsScriptBlock.h"

#include "de-tjs-script.h"
#include "de-tjs-storage.h"
#include "de-tjs-system.h"

#include "de-scripts-tjs.h"
#include "de-tjs-bind.h"
#include "de.h"

NAMESPACE_DE_SCRIPT

static tTJS* s_tjs = null;

void initialize()
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
//        TJS_REGIST_CLASS(Actions)
        
        TVPLoadMessage();
//        REGIST_TJS_FUNCTION(TJSPrint,"print")
//        REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
        
        // AutoRegisterで登録されたクラス等を登録する
        ncbAutoRegister::AllRegist();
        
    }
}

void exec_storage(const de_string& filename,de_var* ret)
{
    LOAD_FILE(data,filename,)
    push_script_file(filename);
    exec(data->getWChar(),ret);
    pop_script_file();
}

void eval_storage(const de_string& filename,de_var* ret)
{
    LOAD_FILE(data,filename,)
    push_script_file(filename);
    eval(data->getWChar(),ret);
    pop_script_file();
}

void exec(const de_char* code,de_var* ret)
{
    initialize();
    if (code == null) {
        return;
    }
    try {
        s_tjs->ExecScript ( code,
                           ret, NULL,
                           NULL ) ;
    }
    TJS_CATCH
}

void eval(const de_char* code,de_var* ret)
{
    initialize();
    if (code == null) {
        return;
    }
    try {
        s_tjs->EvalExpression ( code,
                           ret, NULL,
                           NULL ) ;
    }
    TJS_CATCH
}

static stack<de_string>* s_script_file_stack = new stack<de_string>();

void push_script_file(const de_string& filename)
{
    s_script_file_stack->push(filename);
}

void pop_script_file()
{
    s_script_file_stack->pop();
}

de_string get_cur_file()
{
    if (s_script_file_stack->size() == 0) {
        return de_w("");
    }
    return s_script_file_stack->top();
}

void* script_global()
{
    initialize();
    return s_tjs->GetGlobal();
}

NAMESPACE_DE_END2