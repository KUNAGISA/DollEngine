//
//  GLShaderObject.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLShaderObject__
#define __DollEngine__GLShaderObject__

#include "Units.h"

DE_BEGIN

enum SHADER_TYPE
{
    SHADER_TYPE_VERTEX = 0,
    SHADER_TYPE_FRAGMENT
};

class GLShaderObject
{
public:
    GLShaderObject();
    ~GLShaderObject();
    bool compileShaderCode(const char* code);
    
    PROPERTY(GLuint, Id, m_id){m_id=v;}
    PROPERTY(SHADER_TYPE, Type, m_type){m_type=v;}
};

DE_END

#endif /* defined(__DollEngine__GLShaderObject__) */
