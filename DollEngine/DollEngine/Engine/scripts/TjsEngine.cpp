//
//  TjsEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsEngine.h"
#include "TjsBind.h"
#include "TjsApplication.h"
#include "TjsStorages.h"
#include "TjsScripts.h"
#include "Debug.h"

DE_BEGIN

void Debug::throwMsg(DEBUG_MSG error,const string& p1)
{
    wstring msg;
    switch (error) {
        case ERROR_IMAGE_LOAD_FAILD:
            msg = UnicodeWithFormat(L"图片资源加载失败:%s",p1.c_str());
            break;
        case ERROR_FILE_EXIST_FAILD:
            msg = UnicodeWithFormat(L"文件未找到:%s",p1.c_str());
            break;
        case ERROR_ADDFONT_FAILD:
            msg = UnicodeWithFormat(L"添加字体时出错");
            break;
        default:
            msg = UnicodeWithFormat(L"未知错误");
            break;
    }
    TJS_eTJSError(msg);
}

void Debug::throwMsg(const string &v)
{
    wstring msg;
    Utf8ToUnicode(v.c_str(), msg);
    TJS_eTJSError(msg);
}

static TJS::tTJS* s_tjs = null;
ScriptEngine* ScriptEngine::Engine=null;

TJS::tTJS* TjsEngine::Global()
{
    return s_tjs;
}

TjsEngine* TjsEngine::GetSelf()
{
    return dynamic_cast<TjsEngine*>(ScriptEngine::Engine);
}

TjsEngine::TjsEngine()
{
    ScriptEngine::Engine = this;
    if (!s_tjs)
    {
        s_tjs = new tTJS();
        
        tTJSVariant val;
        iTJSDispatch2 *dsp;
        iTJSDispatch2* global = s_tjs->GetGlobalNoAddRef () ;
        TJS_REGIST_CLASS(Application)
        TJS_REGIST_CLASS(Storages)
        TJS_REGIST_CLASS(Scripts)
        
        TVPLoadMessage();
        TJS_REGIST_FUNCTION(TJSPrint,"print")
        //        REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
        
        // AutoRegisterで登録されたクラス等を登録する
        ncbAutoRegister::AllRegist();
        
    }
}

void TjsEngine::catchError(void* error)
{
    TJS::eTJSScriptError& e = *(TJS::eTJSScriptError*)error;
    TJS::ttstr message;
    message += L"\n【ERROR】\n==>FILE: ";
    wstring curFile;
    Utf8ToUnicode(DE::TjsEngine::GetSelf()->topFile().c_str(), curFile);
    message += curFile;
    message += L"\n\n==>LINE:";
    message += UnicodeWithFormat(L"%d",e.GetSourceLine());
    message += L" ";
    int lineLength=0;
    tTJSScriptBlock* block = e.GetBlockNoAddRef();
    tjs_char* src = block->GetLine(e.GetSourceLine()-1, &lineLength);
    ttstr linecode(src,lineLength);
    message += linecode;
    message += L"\n\n==>MSG: ";
    message += e.GetMessage();
    message += L"\n\n==>STACK: ";
    ttstr tra = e.GetTrace();
    tjs_char* ch = (tjs_char*)tra.c_str();
    while (*ch != 0)
    {
        if (*ch == L'<' &&
            *(ch+1) == L'-' &&
            *(ch+2) == L'-')
        {
            ch+=3;
            message += L"\n<--";
        }
        else
        {
            message += *ch;
            ++ch;
        }
    }
    message += L"\n【ERROR】\n";
    TVPAddLog(message);
}

bool TjsEngine::eval(const wstring& code,void* ret)
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

bool TjsEngine::exec(const wstring& code,void* ret)
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


DE_END
