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
}\
ttstr getClass()\
{\
return _self->ClassNames[0];\
}\
Tjs##CLASS():_self(null)


#define TJS_FACTORY \
Factory(&TjsFactory::factory<ClassT>);\
NCB_PROPERTY_RO(class, getClass);


#define TJS_PRO_SET(obj,key,var) obj->PropSet(TJS_MEMBERENSURE,key,NULL,&var,obj)
#define TJS_PRO_SET_BY_NUM(obj,index,var) obj->PropSetByNum(TJS_MEMBERENSURE,index,&var,obj)

#define TJS_GET_ADAPTOR(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::CreateAdaptor((TYPE*)NODE))

#define TJS_GET_OBJECT(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::GetNativeInstance(NODE));

#define TJS_GET_ARRAY_NI(obj,ni) \
tTJSArrayNI *ni; \
if(TJS_FAILED(obj->NativeInstanceSupport(TJS_NIS_GETINSTANCE,TJSGetArrayClassID(),(iTJSNativeInstance**)&ni))){TJS_eTJSError(TJSSpecifyArray);}


#define iTJSCreateDictionary(ret) \
iTJSDispatch2 *ret = TJSCreateDictionaryObject();\
tTJSVariant ret##_var = tTJSVariant(ret, ret);\
ret->Release();

#define iTJSCreateArray(ret) \
iTJSDispatch2 *ret = TJSCreateArrayObject();\
tTJSVariant ret##_var = tTJSVariant(ret, ret);\
ret->Release();

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