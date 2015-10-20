//
//  PaintShader.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__PaintShader__
#define __DollEngine__PaintShader__

#include "CoreTypes.h"

DE_BEGIN

enum SHADER_TYPE
{
    SHADER_TYPE_VERTEX = 0,
    SHADER_TYPE_FRAGMENT
};

class PaintShader
{
public:
    PaintShader();
    ~PaintShader();
    bool compileShaderCode(const char* code);
    
    PROPERTY(GLuint, Id, m_id){m_id=v;}
    PROPERTY(SHADER_TYPE, Type, m_type){m_type=v;}
};

DE_END

#endif /* defined(__DollEngine__PaintShader__) */
