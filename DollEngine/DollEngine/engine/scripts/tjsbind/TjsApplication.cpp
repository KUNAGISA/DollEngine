//
//  TjsApplication.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsApplication.h"
#include "Application.h"
#include "TjsGameObject.h"

tjs_uint32 tTJSNC_Application::ClassID = -1;
tTJSNC_Application::tTJSNC_Application() : inherited(TJS_W("Application"))
{
    TJS_BEGIN_NATIVE_MEMBERS(Application)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/Application)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/Application)
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
    
    //--property
    
    //----------------------------------------------------------------------
    
    TJS_BEGIN_NATIVE_PROP_DECL(appPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            wstring path;
            DE::Utf8ToUnicode(DEApplication->getAppPath().c_str(),path);
            *result = path;
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
            wstring path;
            DE::Utf8ToUnicode(DEApplication->getDataPath().c_str(),path);
            *result = path;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(dataPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(saveDataPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            wstring path;
            DE::Utf8ToUnicode(DEApplication->getSaveDataPath().c_str(),path);
            *result = path;
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
            wstring path;
            DE::Utf8ToUnicode(DEApplication->getPatchPath().c_str(),path);
            *result = path;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(patchPath)
    
    
    TJS_BEGIN_NATIVE_PROP_DECL(world)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            DE::GameObject* obj = DEApplication->getWorld();
            *result = TJS_GET_ADAPTOR(TjsGameObject, obj);
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_BEGIN_NATIVE_PROP_SETTER
        {
            iTJSDispatch2* dis =(*param).AsObjectNoAddRef();
            TjsGameObject* obj = TJS_GET_OBJECT(TjsGameObject,dis);
            DEApplication->setWorld(obj);
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(world)
    
//    TJS_NATIVE_PROP(graphicCacheLimit,
//                    System::GetInstance()->getGraphicCacheLimit(),
//                    System::GetInstance()->setGraphicCacheLimit(param->AsReal()))
//    TJS_NATIVE_PROP_RO(exeName,System::GetInstance()->getExeName().c_str())
//    TJS_NATIVE_PROP_RO(exePath,System::GetInstance()->getExePath().c_str())
//    TJS_NATIVE_PROP_RO(appDataPath,System::GetInstance()->getAppDataPath().c_str())
//    TJS_NATIVE_PROP_RO(personalPath,System::GetInstance()->getPersonalPath().c_str())
//    TJS_NATIVE_PROP_RO(patchPath,System::GetInstance()->getPatchPath().c_str())
    
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_Application::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}
