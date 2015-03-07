//
//  de-painter-shaderobject.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-painter-shaderobject.h"
#include "de.h"

NAMESPACE_DE_PAINTER

ShaderObject::ShaderObject(SHADER_TYPE type)
:m_id(0),
m_type(type)
{
    
}

ShaderObject::~ShaderObject()
{
    if (m_id)
    {
        glDeleteShader(m_id);
    }
}

bool ShaderObject::compileShaderCode(const char* code)
{
    switch (m_type)
    {
        case SHADER_TYPE_FRAGMENT:
            m_id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case SHADER_TYPE_VERTEX:
            m_id = glCreateShader(GL_VERTEX_SHADER);
            break;
        default:
            break;
    }
    CHECK_GL_ERROR;
    if (m_id)
    {
        string code;
        const GLchar* ptr[] = {code.c_str()};
        glShaderSource(m_id,sizeof(ptr)/sizeof(*ptr), ptr, null);
        glCompileShader(m_id);
        CHECK_GL_ERROR;
        //检查
        GLint compiled;
        glGetShaderiv ( m_id, GL_COMPILE_STATUS, &compiled );
        if ( !compiled )
        {
            GLint infoLen = 0;
            
            
            glGetShaderiv ( m_id, GL_INFO_LOG_LENGTH, &infoLen );
            
            if ( infoLen > 1 )
            {
                char infoLog[infoLen+1];
                memset(infoLog, 0, infoLen+1);
                
                glGetShaderInfoLog ( m_id, infoLen, NULL, infoLog );
                DM("Error compiling shader:\n%s", (const char*)infoLog);
            }
            
            glDeleteShader ( m_id );
            m_id=0;
            return false;
        }
        return true;
    }
    return false;
}

NAMESPACE_DE_END2
