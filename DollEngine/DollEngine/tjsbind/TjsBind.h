//
//  de-tjs-bind.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_tjs_bind__
#define __DollEngine__de_tjs_bind__

#include "Units.h"
#include "ncbind.hpp"


#define TJS_CATCH \
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
de_string stack; \
tjs_char* ch = (tjs_char*)tra.c_str(); \
while (*ch != 0) \
{ \
if (*ch == de_w('<') && \
*(ch+1) == de_w('-') && \
*(ch+2) == de_w('-')) \
{ \
ch+=3; \
stack += de_w("\n<--"); \
} \
else \
{ \
stack += *ch; \
++ch; \
} \
} \
DM("【ERROR--】\n%ls\n(#%d)%ls\n(%ls)\n%ls\n【--ERROR】", \
de::script::get_cur_file().c_str(), \
l,source.c_str(),tr.c_str(),stack.c_str()); \
}


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
virtual ~CLASS(){ \
}\
ttstr getClass()\
{\
return _self->ClassNames[0];\
}\
CLASS()

#define TJS_FACTORY \
Factory(&deTJSFactory::factory<ClassT>);\
NCB_PROPERTY_RO(class, getClass);

class deTJSClass
{
public:
    deTJSClass();
    virtual ~deTJSClass();
    tTJSCustomObject* _self;
};

class deTJSFactory {
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


#endif /* defined(__DollEngine__de_tjs_bind__) */
