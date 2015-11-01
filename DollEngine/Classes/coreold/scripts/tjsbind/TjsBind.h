//
//  de-tjs-bind.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__TjsBind__
#define __DollEngine__TjsBind__

#include "CoreUnits.h"
#include "TjsEngine.h"
#include "ncbind.hpp"
#include "tjs.h"
#include "tjsNative.h"
#include "tjsError.h"
#include "tjsString.h"
#include "tjsVariant.h"
#include "tjsDebug.h"
#include "tjsScriptBlock.h"

using namespace DE;


#define TJS_CATCH catch ( TJS::eTJSScriptError &e ){ DE::ScriptEngine::GetInstance()->catchError(&e);}


#define TJS_EVENT_CALL(NAME,NUM,...) \
static ttstr eventName(TJS_W(#NAME));\
tTJSVariant* param[] = {__VA_ARGS__};\
tTJSVariant result;\
try{\
_self->FuncCall(0, eventName.c_str(), eventName.GetHint(), &result, NUM, param, _self);\
}TJS_CATCH

#define TJS_NATIVE_CLASS_H(classname) \
class tTJSNC_##classname : public tTJSNativeClass \
{\
typedef tTJSNativeClass inherited;\
public:\
tTJSNC_##classname();\
static tjs_uint32 ClassID;\
protected:\
tTJSNativeInstance* CreateNativeInstance();\
};


#define TJS_NATIVE_FUNCTION_BEGIN(name) class name : public tTJSNativeFunction\
{\
protected :\
tjs_error Process(tTJSVariant *result, tjs_int numparams,tTJSVariant **param, iTJSDispatch2 *objthis){

#define TJS_NATIVE_FUNCTION_END }};


#define TJS_REGIST_FUNCTION(FUNC,NAME) \
{\
iTJSDispatch2 * func = new FUNC () ;\
tTJSVariant func_var(func) ;\
func->Release () ;\
TJS_THROW_IF_ERROR (global->PropSet ( TJS_MEMBERENSURE, TJS_W(NAME), NULL, &func_var, global ) );\
}

#define TJS_REGIST_CLASS(classname) \
dsp = new tTJSNC_##classname; \
val = tTJSVariant(dsp/*, dsp*/); \
dsp->Release(); \
global->PropSet(TJS_MEMBERENSURE|TJS_IGNOREPROP, TJS_W(#classname), NULL, \
&val, global);

#define TJS_NATIVE_PROP_RO(name,value) \
TJS_BEGIN_NATIVE_PROP_DECL(name) \
{\
TJS_BEGIN_NATIVE_PROP_GETTER\
{\
*result = value;\
return TJS_S_OK;\
}\
TJS_END_NATIVE_PROP_GETTER\
TJS_DENY_NATIVE_PROP_SETTER\
}\
TJS_END_NATIVE_STATIC_PROP_DECL(name)

#define TJS_NATIVE_PROP(name,GET,SET) \
TJS_BEGIN_NATIVE_PROP_DECL(name) \
{\
TJS_BEGIN_NATIVE_PROP_GETTER\
{\
*result = GET;\
return TJS_S_OK;\
}\
TJS_END_NATIVE_PROP_GETTER \
TJS_BEGIN_NATIVE_PROP_SETTER\
{\
SET;\
return TJS_S_OK;\
}\
TJS_END_NATIVE_PROP_SETTER\
}\
TJS_END_NATIVE_STATIC_PROP_DECL(name)


#define TJS_NCB(CLASS) \
class Tjs##CLASS : public DE::CLASS\
{\
public:\
tTJSCustomObject* _self;\
virtual ~Tjs##CLASS(){ \
for(tjs_int i=TJS_MAX_NATIVE_CLASS-1; i>=0; i--)\
{\
    if(_self->ClassIDs[i]!=-1)\
    {\
        if(_self->ClassInstances[i]) {\
            ncbInstanceAdaptor<Tjs##CLASS>* d= dynamic_cast<ncbInstanceAdaptor<Tjs##CLASS>*>(_self->ClassInstances[i]);\
            if(d){\
                d->setSticky();\
            }\
        }\
    }\
}\
_self->_Finalize();\
}\
tTJSVariant getClass()\
{\
return _self->ClassNames[0];\
}\
Tjs##CLASS():_self(null)

#define TJS_NCB_COM(CLASS) TJS_NCB(CLASS){}\
void setCompName(tTJSVariant v){\
TJS_STRING(v,name)\
Component::setCompName(name);\
}\
tTJSVariant getCompName(){\
    wstring name;\
    Utf8ToUnicode(m_compName.c_str(), name);\
    return name.c_str();\
} \
tTJSVariant getObject() {\
    auto obj = dynamic_cast<TjsGameObject*>(CLASS::getObject());\
    if (obj) {\
        return obj->_self;\
    } else {\
        return tTJSVariant();\
    }\
}\
void setObject(tTJSVariant v){\
    if (v.Type() == tvtVoid) {\
        auto obj = dynamic_cast<TjsGameObject*>(CLASS::getObject());\
        if(obj){\
            obj->_self->Release();\
        }\
        CLASS::setObject(null);\
        return;\
    }\
    TjsGameObject* obj = TJS_GET_OBJECT(TjsGameObject, v.AsObject());\
    CLASS::setObject(obj);\
}

#define TJS_FACTORY_COM \
TJS_FACTORY \
NCB_METHOD(update);\
NCB_PROPERTY(enabled, getEnabled, setEnabled); \
NCB_PROPERTY(object,getObject,setObject); \
NCB_PROPERTY(time, getTime, setTime);\
NCB_PROPERTY(type, getType, setType);\
NCB_PROPERTY(name, getCompName, setCompName);

#define TJS_FACTORY \
Factory(&TjsFactory::factory<ClassT>);\
NCB_METHOD(getClass);

#define TJS_STRING(v,str) string str;\
UnicodeToUtf8(v.AsStringNoAddRef()->operator const wchar_t *(), str);

#define TJS_WSTRING(v,str) wstring str;\
Utf8ToUnicode(v.c_str(), str);

#define TJS_GET_DISPATCH(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::GetAdaptor((TYPE*)NODE))

#define TJS_GET_OBJECT(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::GetNativeInstance(NODE));

class TjsFactory {
public:
    template <typename TYPE>
    static tjs_error factory(TYPE **result, tjs_int numparams, tTJSVariant **params, iTJSDispatch2 *objthis)
    {
        TYPE *pObject = new TYPE();
        tTJSCustomObject* obj = dynamic_cast<tTJSCustomObject*>(objthis);
        ASSERT(obj);
        pObject->_self =  obj;
        *result = pObject;
        return TJS_S_OK;
    }
};


#endif /* defined(__DollEngine__TjsBind__) */
