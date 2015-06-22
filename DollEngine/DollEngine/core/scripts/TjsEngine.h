//
//  TjsEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsEngine__
#define __DollEngine__TjsEngine__

#include "ScriptEngine.h"

DE_BEGIN

class TjsEngine : public ScriptEngine
{
public:
    TjsEngine();
    Shared(TjsEngine)
    virtual bool eval(const string& code);
    virtual bool evalStorage(const string& filePath);
    virtual bool exec(const string& code);
    virtual bool execStorage(const string& filePath);
};

DE_END

#endif /* defined(__DollEngine__TjsEngine__) */
