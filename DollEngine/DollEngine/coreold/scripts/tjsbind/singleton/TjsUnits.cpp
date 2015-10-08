//
//  TjsUnits.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/21.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsUnits.h"

tjs_uint32 tTJSNC_Units::ClassID = -1;
tTJSNC_Units::tTJSNC_Units() : inherited(TJS_W("Units"))
{
    TJS_BEGIN_NATIVE_MEMBERS(Units)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/Units)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/Units)
    //----------------------------------------------------------------------
    
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/colorBy4F)
    {
        if ( numparams <4 ) return TJS_E_BADPARAMCOUNT ;
        Color c;
        tTJSVariant* v = param[0];
        tjs_int32 k = v->AsReal()*255;
        c.r = k;
        v = param[1];
        k = v->AsReal()*255;
        c.g = k;
        v = param[2];
        k = v->AsReal()*255;
        c.b = k;
        v = param[3];
        k = v->AsReal()*255;
        c.a = k;
        
        uint32_t r;
        c.toInt32(r);
        (*result) = (long long)r;
        return TJS_S_OK ;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/colorBy4F)
    
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/colorBy4B)
    {
        if ( numparams <4 ) return TJS_E_BADPARAMCOUNT ;
        Color c((int)param[0]->AsInteger(),(int)param[1]->AsInteger(),(int)param[2]->AsInteger(),(int)param[3]->AsInteger());
        uint32_t r;
        c.toInt32(r);
        (*result) = (long long)r;
        return TJS_S_OK ;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/colorBy4B)
    
    
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_Units::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}