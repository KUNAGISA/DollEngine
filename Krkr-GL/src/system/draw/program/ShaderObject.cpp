//
//  ShaderObject.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "ShaderObject.h"
#include "Storages.h"
#include "IOData.h"

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

bool ShaderObject::compileShaderFile(const wstring& file_name)
{
    IOData* data = Storages::GetFileText(Storages::GetInstance()->getFullPath(file_name));
    if (!data) {
        return false;
    }
    bool ret = compileShaderCode((const char*)data->getBuffer());
    delete data;
    return ret;
}
