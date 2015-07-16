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
#include "ncbind.hpp"
#include "tjs.h"
#include "tjsNative.h"
#include "tjsError.h"
#include "tjsString.h"
#include "tjsVariant.h"
#include "tjsDebug.h"
#include "tjsScriptBlock.h"


#define TJS_CATCH catch ( TJS::eTJSScriptError &e ){ DE::ScriptEngine::GetInstance()->catchError(&e);}


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
public :\
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


#define TJS_GET_ADAPTOR(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::CreateAdaptor((TYPE*)NODE))

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


TJS_NATIVE_FUNCTION_BEGIN(TJSPrint)
if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
tTJSVariant* str = param[0];
if(str)
{
    if(str->Type() == tvtVoid)
    {
        DM("[TJS]:(void)");
        return TJS_S_OK;
    }
    ttstr str_s = *str;
    auto ptr = str_s.AsVariantStringNoAddRef();
    if(ptr)
    {
        DM("[TJS]:%ls",str_s.AsStdString().c_str());
        return TJS_S_OK;
    }
    else
    {
        DM("[TJS]:(null)");
        return TJS_S_OK;
    }
}
return TJS_S_OK ;
TJS_NATIVE_FUNCTION_END

TJS_NATIVE_FUNCTION_BEGIN(TJSPrintTime)
printf("%lld\n",DE::GetMilliSeconds());
return TJS_S_OK ;
TJS_NATIVE_FUNCTION_END

#endif /* defined(__DollEngine__TjsBind__) */
