//
//  ShaderProgram.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    for (ShaderObject* obj : m_shaders)
    {
        glDetachShader(m_programId,obj->getId());
        delete obj;
    }
    m_shaders.clear();
    glDeleteProgram(m_programId);
}

void ShaderProgram::addShader(ShaderObject* object)
{
    m_shaders.push_back(object);
    glAttachShader(m_programId,object->getId());
    CHECK_GL_ERROR;
}

void ShaderProgram::addShaderFromCode(ShaderObject::SHADER_TYPE type, const char* code)
{
    ShaderObject* object = new ShaderObject(type);
    object->compileShaderCode(code);
    addShader(object);
}

bool ShaderProgram::bind()
{
    bindAttributeLocation("a_position",PROGRAM_VERTEX_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("a_color",PROGRAM_COLOR_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("a_texCoord",PROGRAM_TEXCOORD_ATTRIBUTE);
    CHECK_GL_ERROR;
    //    bind(PROGRAM_OPACITY_ATTRIBUTE,"a_opacity");
    if(!link())
    {
        return false;
    }
    bindAttributeLocation("texture_normal",PROGRAM_TEXTURE_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("texture_fbo",PROGRAM_FBO_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("matrix",PROGRAM_MATRIX_ATTRIBUTE);
    CHECK_GL_ERROR;
    
    int index =glGetUniformLocation(m_programId,"texture_normal");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["texture_normal"]=index;
    
    index =glGetUniformLocation(m_programId,"matrix");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["matrix"]=index;
    
    index =glGetUniformLocation(m_programId, "texture_fbo");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["texture_fbo"]=index;
    
    use();
    setUniformValue("texture_normal",0);
    CHECK_GL_ERROR;
    return true;
}

void ShaderProgram::bindAttributeLocation(const char * name, int location)
{
    glBindAttribLocation(m_programId,location,name);
    CHECK_GL_ERROR;
}

bool ShaderProgram::link()
{
    glLinkProgram(m_programId);
    CHECK_GL_ERROR;
    
    GLint status;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &status);
    CHECK_GL_ERROR;
    if (status == 0) {
        return false;
    }
    return true;
}

void ShaderProgram::use()
{
    GL::useProgram(m_programId);
    CHECK_GL_ERROR;
}

void ShaderProgram::setUniformValue(const char* name,GLfloat value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1f(iter->second, value);
    CHECK_GL_ERROR;
}

void ShaderProgram::setUniformValue(const char* name,GLint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1i(iter->second, value);
    CHECK_GL_ERROR;
}

void ShaderProgram::setUniformValue(const char* name,GLuint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1i(iter->second, value);
    CHECK_GL_ERROR;
}

void ShaderProgram::setUniformValue(const char* name,const kmMat4& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        glUniformMatrix4fv(iter->second, 1,GL_FALSE,(GLfloat*)value.mat);
    }
    CHECK_GL_ERROR;
}
