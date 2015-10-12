//
//  TjsSet.h
//  DollEngine
//
//  Created by DollStudio on 15/8/9.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsSet__
#define __DollEngine__TjsSet__

#include "TjsBind.h"

DE_BEGIN

class TjsSet
{
public:
    tTJSCustomObject* _self;
    tTJSVariant getClass()
    {
        return _self->ClassNames[0];
    }
    TjsSet():_self(NULL){
    }
    ~TjsSet(){
        clear();
    }
    void add(tTJSVariant v){
        String key = v.AsString()->operator const wchar_t *();
        if(m_all.find(key)==m_all.end()){
            m_all[key] = v;
        }
    }
    void remove(tTJSVariant v){
        String key = v.AsString()->operator const wchar_t *();
        m_all.erase(key);
    }
    void clear(){
        m_all.clear();
    }
    void assign(tTJSVariant v){
        clear();
        TjsSet* obj = TJS_GET_OBJECT(TjsSet, v.AsObjectNoAddRef());
        if (obj) {
            for (auto iter = obj->m_all.begin();
                 iter != obj->m_all.end(); ++iter)
            {
                m_all[iter->first] = iter->second;
            }
        }
    }
    size_t count(){
        return m_all.size();
    }
#ifdef __QT__
    void toForeach(tTJSVariant v){
#else
    void foreach(tTJSVariant v){
#endif
        iTJSDispatch2* objthis = v.AsObjectThisNoAddRef();
        iTJSDispatch2* f = v.AsObjectNoAddRef();
        tTJSInterCodeContext* func = dynamic_cast<tTJSInterCodeContext*>(f);
        if (func) {
            map<String,tTJSVariant> tmp = m_all;
            for (auto iter = tmp.begin();
                 iter != tmp.end(); ++iter)
            {
                tTJSVariant* params = {&iter->second};
                func->FuncCall(0, NULL, NULL, NULL, 1, &params, objthis);
            }
        }
    }
protected:
    map<String,tTJSVariant> m_all;
};

DE_END


#endif /* defined(__DollEngine__TjsSet__) */
