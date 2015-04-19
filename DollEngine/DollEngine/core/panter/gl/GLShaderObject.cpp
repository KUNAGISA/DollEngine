//
//  GLShaderObject.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLShaderObject.h"

DE_BEGIN

GLShaderObject::GLShaderObject()
:m_id(0)
{
    
}

GLShaderObject::~GLShaderObject()
{
    if (m_id)
    {
        glDeleteShader(m_id);
    }
}

bool GLShaderObject::compileShaderCode(const char* code)
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
        const GLchar* ptr[] = {code};
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
//                DM("Error compiling shader:\n%s", (const char*)infoLog);
            }
            
            glDeleteShader ( m_id );
            m_id=0;
            return false;
        }
        return true;
    }
    return false;
}

DE_END