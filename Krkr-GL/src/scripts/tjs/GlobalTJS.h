//
//  GlobalTJS.h
//  DollEngine
//
//  Created by DollStudio on 14/11/14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GlobalTJS__
#define __DollEngine__GlobalTJS__

#include "tjs.h"
#include "ncbind.hpp"
#include "tjsNative.h"
#include "tjsError.h"
#include "tjsString.h"
#include "tjsVariant.h"
#include "tjsDebug.h"
#include "tjsScriptBlock.h"
#include "StringUtils.h"

#define iTJSErrorCatch \
catch ( TJS::eTJSScriptError &e ) \
{ \
    tjs_int l = e.GetSourceLine(); \
    TJS::ttstr tr = e.GetMessage(); \
    tTJSScriptBlock* block = e.GetBlockNoAddRef(); \
    \
    int lineLength=0; \
    tjs_char* src = block->GetLine(l-1, &lineLength); \
    ttstr source(src,lineLength); \
    ttstr tra = e.GetTrace(); \
    wstring stack; \
    tjs_char* ch = (tjs_char*)tra.c_str(); \
    while (*ch != 0) \
    { \
        if (*ch == L'<' && \
            *(ch+1) == L'-' && \
            *(ch+2) == L'-') \
        { \
            ch+=3; \
            stack += L"\n<--"; \
        } \
        else \
        { \
            stack += *ch; \
            ++ch; \
        } \
    } \
    DM("【--ERROR--ERROR--ERROR--ERROR--ERROR--ERROR】\n%ls\n(#%d)%ls\n(%ls)\n%ls\n【ERROR--ERROR--ERROR--ERROR--ERROR--ERROR--】", \
       Scripts::GetInstance()->getFile().c_str(), \
       l,source.c_str(),tr.c_str(),stack.c_str()); \
}


#define iTJSEventCall(NAME,NUM,...) \
static ttstr eventName(TJS_W(#NAME));\
tTJSVariant* param[] = {__VA_ARGS__};\
tTJSVariant result;\
try{\
m_tjsObject->FuncCall(0, eventName.c_str(), eventName.GetHint(), &result, NUM, param, m_tjsObject);\
}iTJSErrorCatch

#define iTJSGetAdaptor(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::CreateAdaptor((TYPE*)NODE))
#define iTJSGetObject(TYPE,NODE) (ncbInstanceAdaptor<TYPE>::GetNativeInstance(NODE));

#define iTJSCreateDictionary(ret) \
iTJSDispatch2 *ret = TJSCreateDictionaryObject();\
tTJSVariant ret##_var = tTJSVariant(ret, ret);\
ret->Release();

#define iTJSCreateArray(ret) \
iTJSDispatch2 *ret = TJSCreateArrayObject();\
tTJSVariant ret##_var = tTJSVariant(ret, ret);\
ret->Release();

#define iTJSProSet(obj,key,var) obj->PropSet(TJS_MEMBERENSURE,key,NULL,&var,obj)
#define iTJSProSetByNum(obj,index,var) obj->PropSetByNum(TJS_MEMBERENSURE,index,&var,obj)

#define TJSNativeFunctionStart(name) class name : public tTJSNativeFunction\
{\
public :\
tjs_error Process(tTJSVariant *result, tjs_int numparams,tTJSVariant **param, iTJSDispatch2 *objthis){

#define TJSNativeFunctionEnd }};

#define REGIST_TJS_FUNCTION(FUNC,NAME) \
{\
iTJSDispatch2 * func = new FUNC () ;\
tTJSVariant func_var(func) ;\
func->Release () ;\
TJS_THROW_IF_ERROR (global->PropSet ( TJS_MEMBERENSURE, TJS_W(NAME), NULL, &func_var, global ) );\
}

#define REGIST_TJS_CLASS(classname) \
dsp = new tTJSNC_##classname; \
val = tTJSVariant(dsp/*, dsp*/); \
dsp->Release(); \
global->PropSet(TJS_MEMBERENSURE|TJS_IGNOREPROP, TJS_W(#classname), NULL, \
&val, global);

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

#define iTJS_METHOD_OBJECT(TYPE,FUNC,CLASS) \
void FUNC(tTJSVariant v)\
{\
TJS##TYPE* src = iTJSGetObject(TJS##TYPE, v.AsObjectNoAddRef());\
CLASS::FUNC(src);\
}

#define iTJS_SET_OBJECT(TYPE,NAME,CLASS) iTJS_METHOD_OBJECT(TYPE,set##NAME,CLASS)

#define iTJS_GET_OBJECT(TYPE,NAME,CLASS) \
tTJSVariant get##NAME()\
{\
    TJS##TYPE* obj = dynamic_cast<TJS##TYPE*>(CLASS::get##NAME());\
    return iTJSGetAdaptor(TJS##TYPE,obj);\
}

#define iTJS_PROPERTY_OBJECT(TYPE,NAME,CLASS) \
iTJS_SET_OBJECT(TYPE,NAME,CLASS)\
iTJS_GET_OBJECT(TYPE,NAME,CLASS)\

#define iTJS_SET_STR(CLASS,NAME) \
void set##NAME(ttstr v){\
CLASS::set##NAME(v.AsStdString());\
}

#define iTJS_GET_STR(CLASS,NAME) \
ttstr get##NAME(){\
    return CLASS::get##NAME();\
}

#define iTJS_PROPERTY_STR(CLASS,NAME) \
iTJS_SET_STR(CLASS,NAME)\
iTJS_GET_STR(CLASS,NAME)\

#define iTJS_FACTORY \
Factory(&TJSFactory::factory<ClassT>);\
NCB_PROPERTY_RO(class, getClass);

#define iTJS_FACTORY_COM \
iTJS_FACTORY \
NCB_METHOD(release);\
NCB_METHOD(trigger);\
NCB_PROPERTY(name, getComName, setComName);\
NCB_PROPERTY(object, getObject, setObject);\
NCB_PROPERTY(triggerType, getTriggerType, setTriggerType);\
NCB_PROPERTY(enabled, getEnabled, setEnabled);


#define iTJS_NCB(CLASS) \
CLASS():m_tjsObject(null){}\
tTJSCustomObject* m_tjsObject;\
virtual ~CLASS(){ \
}\
ttstr getClass()\
{\
    return m_tjsObject->ClassNames[0];\
}

//if(m_tjsObject && !m_tjsObject->IsInvalidated) \
//ncbInstanceAdaptor<CLASS>::GetAdaptor(m_tjsObject)->setSticky(); \


#define iTJS_COM(CLASS) \
class TJS##CLASS : public CLASS\
{\
public:\
iTJS_NCB(TJS##CLASS)\
void release(){\
    ncbInstanceAdaptor<TJS##CLASS>::GetAdaptor(m_tjsObject)->setSticky();\
    CLASS::release();\
}\
iTJS_PROPERTY_OBJECT(Object, Object,CLASS)\
iTJS_PROPERTY_STR(CLASS,ComName)

class TJSFactory {
public:
    template <typename TYPE>
    static tjs_error factory(TYPE **result, tjs_int numparams, tTJSVariant **params, iTJSDispatch2 *objthis)
    {
        TYPE *pObject = new TYPE();
        tTJSCustomObject* obj = dynamic_cast<tTJSCustomObject*>(objthis);
        ASSERT(obj);
        pObject->m_tjsObject =  obj;
        *result = pObject;
        return TJS_S_OK;
    }
};

TJSNativeFunctionStart(TJSPrint)
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
TJSNativeFunctionEnd

TJSNativeFunctionStart(TJSConsoleShow)
if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
//int visible = param[0]->AsInteger() ;
return TJS_S_OK ;
TJSNativeFunctionEnd


class TJSTextReadStream : public iTJSTextReadStream
{
public:
    virtual tjs_uint TJS_INTF_METHOD Read(tTJSString & targ, tjs_uint size){return 0;}
    virtual void TJS_INTF_METHOD Destruct(){}
};

class TJSTextWriteStream : public iTJSTextWriteStream
{
public:
    virtual void TJS_INTF_METHOD Write(const tTJSString & targ){}
    virtual void TJS_INTF_METHOD Destruct(){} // must delete itself
};

#endif /* defined(__DollEngine__GlobalTJS__) */
