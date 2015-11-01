//
//  PaintShader.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "PaintShader.h"
#include "PaintEngine.h"

DE_BEGIN

PaintShader::PaintShader()
:m_id(0)
{
    
}

PaintShader::~PaintShader()
{
    if (m_id)
    {
        PaintEngine::GetInstance()->deleteShader(m_id);
    }
}

bool PaintShader::compileShaderCode(const char* code)
{
    switch (m_type)
    {
        case SHADER_TYPE_FRAGMENT:
            m_id = PaintEngine::GetInstance()->createShader(GL_FRAGMENT_SHADER,code);
            break;
        case SHADER_TYPE_VERTEX:
            m_id = PaintEngine::GetInstance()->createShader(GL_VERTEX_SHADER,code);
            break;
        default:
            break;
    }
    if (m_id)
    {
        return true;
    }
    return false;
}

DE_END
