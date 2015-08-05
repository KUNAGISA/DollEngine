//
//  TJSKAGParser.h
//  Krkr_GL
//
//  Created by DollStudio on 14/11/22.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__TJSKAGParser__
#define __Krkr_GL__TJSKAGParser__

#include "TjsBind.h"
#include "KAGParser.h"

TJS_NCB(KAGParser){}
virtual void jumpTo(ttstr storage,ttstr label);
virtual void callLabel(ttstr storage,ttstr label);
virtual bool callMacro(ttstr name){
    return KAGParser::callMacro(name.AsStdString());
}
virtual void onScenarioEnded(){
    TJS_EVENT_CALL(onScenarioEnded, 0);
}
virtual int execute(KAGTag* tag);
virtual void onExecute(ttstr name,iTJSDispatch2* params){}
protected:
vector<wstring> m_ifKey;
};

#endif /* defined(__Krkr_GL__TJSKAGParser__) */
