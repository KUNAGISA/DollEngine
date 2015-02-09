//
//  ShaderObject.h
//  Krkr_GL
//
//  Created by DollStudio on 14-9-14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__ShaderObject__
#define __Krkr_GL__ShaderObject__

#include "Functions.h"

class ShaderObject
{
public:
    enum SHADER_TYPE
    {
        SHADER_TYPE_VERTEX = 0,
        SHADER_TYPE_FRAGMENT
    };
    ShaderObject(SHADER_TYPE type);
    ~ShaderObject();
    bool compileShaderCode(const char* code);
    bool compileShaderFile(const wstring& file_name);
public:
    PROPERTY(GLuint, Id, m_id){m_id=v;}
    PROPERTY(SHADER_TYPE, Type, m_type){m_type=v;}
};

#endif /* defined(__Krkr_GL__ShaderObject__) */
