//
//  de-painter-shaderobject.h
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_painter_shaderobject__
#define __DollEngine__de_painter_shaderobject__

#include "de-functions.h"

NAMESPACE_DE_PAINTER

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
public:
    PROPERTY(GLuint, Id, m_id){m_id=v;}
    PROPERTY(SHADER_TYPE, Type, m_type){m_type=v;}
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_painter_shaderobject__) */
