//
//  GLProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLProgram.h"

DE_BEGIN

GLProgram::GLProgram()
{
    m_programId = glCreateProgram();
}

GLProgram::~GLProgram()
{
    for (GLShaderObject* obj : m_shaders)
    {
        glDetachShader(m_programId,obj->getId());
        delete obj;
    }
    m_shaders.clear();
    glDeleteProgram(m_programId);
}

void GLProgram::addShader(SHADER_TYPE type,const char* code)
{
    GLShaderObject* obj = new GLShaderObject();
    obj->setType(type);
    obj->compileShaderCode(code);
    addShader(obj);
}

void GLProgram::addShader(GLShaderObject* obj)
{
    m_shaders.push_back(obj);
    glAttachShader(m_programId,obj->getId());
    CHECK_GL_ERROR;
}

bool GLProgram::bind()
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
    bindAttributeLocation("tex_fore",PROGRAM_TEXTURE_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("tex_back",PROGRAM_TEXTURE_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("texture_fbo",PROGRAM_FBO_ATTRIBUTE);
    CHECK_GL_ERROR;
    bindAttributeLocation("matrix",PROGRAM_MATRIX_ATTRIBUTE);
    CHECK_GL_ERROR;
    
    int index =glGetUniformLocation(m_programId,"tex_fore");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["tex_fore"]=index;
    
    index =glGetUniformLocation(m_programId,"tex_back");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["tex_back"]=index;
    
    index =glGetUniformLocation(m_programId, "texture_fbo");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["texture_fbo"]=index;
    
    index =glGetUniformLocation(m_programId,"matrix");
    CHECK_GL_ERROR;
    if (index != -1) m_allUniformIndex["matrix"]=index;
    
    use();
    setUniformValue("tex_fore",0);
    CHECK_GL_ERROR;
    return true;
}

void GLProgram::bindAttributeLocation(const char * name, int location)
{
    glBindAttribLocation(m_programId,location,name);
    CHECK_GL_ERROR;
}

bool GLProgram::link()
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

static GLuint s_currentProgramId=0;
void GLProgram::use()
{
    if (s_currentProgramId != m_programId) {
        s_currentProgramId = m_programId;
        glUseProgram(m_programId);
        CHECK_GL_ERROR;
    }
}

static int MAX_ATTRIBUTES = 16;
static uint32_t s_attributeFlags = 0;
void GLProgram::enableVertexAttribs(uint32_t flags)
{
    GL::bindVAO(0);
    
    // hardcoded!
    for(int i=0; i < MAX_ATTRIBUTES; i++) {
        unsigned int bit = 1 << i;
        bool enabled = flags & bit;
        bool enabledBefore = s_attributeFlags & bit;
        if(enabled != enabledBefore) {
            if( enabled )
                glEnableVertexAttribArray(i);
            else
                glDisableVertexAttribArray(i);
        }
    }
    s_attributeFlags = flags;
}

void GLProgram::setUniformValue(const char* name,GLfloat value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1f(iter->second, value);
    CHECK_GL_ERROR;
}

void GLProgram::setUniformValue(const char* name,GLint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1i(iter->second, value);
    CHECK_GL_ERROR;
}

void GLProgram::setUniformValue(const char* name,GLuint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1i(iter->second, value);
    CHECK_GL_ERROR;
}

void GLProgram::setUniformValue(const char* name,const kmMat4& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        glUniformMatrix4fv(iter->second, 1,GL_FALSE,(GLfloat*)value.mat);
    }
    CHECK_GL_ERROR;
}

DE_END