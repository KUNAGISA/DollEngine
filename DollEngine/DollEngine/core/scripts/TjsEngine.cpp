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
#include "TjsConsole.h"

DE_BEGIN


TJS_NATIVE_FUNCTION_BEGIN(TJSPrint)
if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
tTJSVariantString *res;
res = TJSFormatString(param[0]->AsString()->operator const wchar_t *(), numparams-1, &param[1]);
DM("【TJS】: %ls",(const tjs_char*)*res);
if(res) res->Release();
return TJS_S_OK ;
TJS_NATIVE_FUNCTION_END

TJS_NATIVE_FUNCTION_BEGIN(TJSPrintTime)
DM("%lld\n",DE::GetMilliSeconds());
return TJS_S_OK ;
TJS_NATIVE_FUNCTION_END


TJS_NATIVE_FUNCTION_BEGIN(TJSThrow)
if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
tTJSVariantString *res;
res = TJSFormatString(param[0]->GetString(), numparams, &param[1]);
if(res) {
    TJS_eTJSError(*res);
}
else {
    TJS_eTJSError(L"");
}
return TJS_S_OK;
TJS_NATIVE_FUNCTION_END

static const int kMaxLogLen = 32*1024;
static char logbuff[sizeof(char) * (kMaxLogLen + 1)];
void Debug::message(const char* format,...)
{
    //    va_list args;
    //    va_start(args, format);
    //    printf(format,args);
    //    va_end(args);
    //    printf("\n");
    va_list args;
    memset(logbuff, 0, sizeof(logbuff));
    va_start(args, format);
    vsprintf(logbuff, format, args);
    va_end(args);
    wstring str;
    Utf8ToUnicode(logbuff, str);
    TjsEngine::Global()->OutputToConsole(str.c_str());
    //
    //    return logbuff;
}

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

void Debug::throwMsg(DEBUG_MSG error,int p1,const wstring& p2)
{
    wstring msg;
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
        default:
            msg = UnicodeWithFormat(L"(#%d)KAG发生未知错误",p1);
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
        TJSEnableDebugMode=true;
        tTJSVariant val;
        iTJSDispatch2 *dsp;
        iTJSDispatch2* global = s_tjs->GetGlobalNoAddRef () ;
        TJS_REGIST_CLASS(Application)
        TJS_REGIST_CLASS(Storages)
        TJS_REGIST_CLASS(Scripts)
        
        TVPLoadMessage();
        TJS_REGIST_FUNCTION(TJSThrow, "throwMsg");
        TJS_REGIST_FUNCTION(TJSPrint,"print")
        TJS_REGIST_FUNCTION(TJSPrintTime, "printTime")
        //        REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
        
        // AutoRegisterで登録されたクラス等を登録する
        ncbAutoRegister::AllRegist();
        
        s_tjs->SetConsoleOutput(TjsConsole::GetInstance());
    }
}

void TjsEngine::catchError(void* error)
{
//    TJS::eTJSScriptError& e = *(TJS::eTJSScriptError*)error;
//    TJS::ttstr message;
//    message += L"\n【ERROR】";
//    message += L"\n==>MSG: ";
//    message += e.GetMessage();
//    message += L"\n==>LINE:";
//    message += UnicodeWithFormat(L"%d",e.GetSourceLine());
//    message += L" ";
//    int lineLength=0;
//    tTJSScriptBlock* block = e.GetBlockNoAddRef();
//    tjs_char* src = block->GetLine(e.GetSourceLine()-1, &lineLength);
//    ttstr linecode(src,lineLength);
//    message += e.SourceName;
//    message += "\n";
//    message += linecode;
//    message += L"\n==>STACK:\n";
//    wstring tra = e.GetTrace().AsStdString();
//    size_t idx = tra.find(L"(");
//    while (idx!=wstring::npos) {
//        size_t idx2 = tra.find(L" <-- anonymous@",idx);
//        wstring sub = tra.substr(idx,idx2-idx);
//        message += L"[trace]";
//        message += sub;
//        message += L"\n";
//        if (idx2 == wstring::npos) {
//            break;
//        }
//        idx = tra.find(L"(",idx2);
//    }
//    message += L"【ERROR】\n";
//    TjsEngine::Global()->OutputExceptionToConsole(message.c_str());
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