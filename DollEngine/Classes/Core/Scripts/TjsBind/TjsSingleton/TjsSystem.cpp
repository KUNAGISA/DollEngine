//
//  TjsSystem.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsSystem.h"
#include "System.h"
#include "PaintEngine.h"
#include "TjsSystemDelegate.h"
#include "TjsTransform.h"

tjs_uint32 tTJSNC_System::ClassID = -1;
tTJSNC_System::tTJSNC_System() : inherited(TJS_W("System"))
{
    TJS_BEGIN_NATIVE_MEMBERS(System)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/System)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/System)
    //----------------------------------------------------------------------
    
    //-- methods
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/exit)
    {
        tjs_int64 code = numparams > 0 ? (*param[0]).AsInteger() : 0;
        exit((int)code);
        
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/exit)
            
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/addFont)
    {
        if(numparams < 1) return TJS_E_BADPARAMCOUNT;
        tTJSVariant* v = param[0];
        DE::String fpath = v->AsString()->operator const tjs_char *();
        DE::String fname = DE::System::GetInstance()->addFont(fpath);
        
        if(fname.empty()) {
            return TJS_E_FAIL;
        }
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/addFont)
            
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/openUrl)
    {
        if(numparams < 1) return TJS_E_BADPARAMCOUNT;
        tTJSVariant* v = param[0];
        DE::String url = v->AsString()->operator const tjs_char *();
        if(url.empty()){
            return TJS_S_OK;
        }
        DE::System::GetInstance()->openUrl(url);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/openUrl)
    
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/doCompact)
    {
        DE::System::GetInstance()->doCompact();
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/doCompact)
    
    //--property
    
    //----------------------------------------------------------------------
            
    TJS_BEGIN_NATIVE_PROP_DECL(delegate)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            TjsSystemDelegate* delegate = dynamic_cast<TjsSystemDelegate*>(DESystem->getDelegate());
            if(delegate){
                *result = delegate->_self;
                return TJS_S_OK;
            }
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_BEGIN_NATIVE_PROP_SETTER
        {
            if(DESystem->getDelegate()){
                EM("SystemDelegate已经存在");
                return TJS_E_FAIL;
            }
            else {
                TjsSystemDelegate* obj = TJS_GET_OBJECT(TjsSystemDelegate,param->AsObjectNoAddRef());
                if(!obj){
                    return TJS_E_INVALIDPARAM;
                }
                DESystem->setDelegate(obj);
            }
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(delegate)
            
    TJS_BEGIN_NATIVE_PROP_DECL(appPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getAppPath();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(appPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(dataPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getDataPath();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(dataPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(gamePath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getGamePath();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(gamePath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(saveDataPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getSaveDataPath();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(saveDataPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(patchPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getPatchPath();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(patchPath)
            
    TJS_BEGIN_NATIVE_PROP_DECL(platformName)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getPlatformName();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(platformName)
            
    TJS_BEGIN_NATIVE_PROP_DECL(versionInformation)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = ENGINE_VERSION;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(versionInformation)
    
    
    TJS_BEGIN_NATIVE_PROP_DECL(desktopWidth)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getDesktopWidth();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(desktopWidth)
    
    TJS_BEGIN_NATIVE_PROP_DECL(desktopHeight)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getDesktopHeight();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(desktopHeight)
    
    TJS_BEGIN_NATIVE_PROP_DECL(milliSeconds)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getMilliSeconds();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(milliSeconds)
    
    TJS_BEGIN_NATIVE_PROP_DECL(seconds)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            *result = DESystem->getSeconds();
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(seconds)
    
    TJS_NATIVE_PROP(debugMode,DESystem->getDebugMode(),DESystem->setDebugMode((int)param->AsInteger()))
    
    
    
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_System::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}
