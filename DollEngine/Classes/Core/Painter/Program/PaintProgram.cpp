//
//  PaintProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "PaintProgram.h"
#include "PaintEngine.h"

DE_BEGIN

PaintProgram::PaintProgram()
{
    m_programId = PaintEngine::GetInstance()->createProgram();
}

PaintProgram::~PaintProgram()
{
    for (PaintShader* obj : m_shaders)
    {
        PaintEngine::GetInstance()->detachShader(m_programId,obj->getId());
        delete obj;
    }
    m_shaders.clear();
    PaintEngine::GetInstance()->deleteProgram(m_programId);
}

const char* PaintProgram::getShader_V()
{
    return
    "uniform mat4 matrix;"
    "attribute vec4 a_position;"
    "attribute vec2 a_texCoord;"
    "attribute vec4 a_color;"
    "\n#ifdef GL_ES\n"
    "varying lowp vec4 v_fragmentColor;"
    "varying mediump vec2 v_texCoord;"
    "\n#else\n"
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    "\n#endif\n"
    "void main()"
    "{"
    "gl_Position = matrix * a_position;"
    "v_fragmentColor = a_color;"
    "v_texCoord = a_texCoord;"
    "}";
}

const char* PaintProgram::getShader_F()
{
    return
    "#ifdef GL_ES\n"
    "precision lowp float;"
    "\n#endif\n"
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    "uniform sampler2D tex_fore;"
    "void main()"
    "{"
    "gl_FragColor = v_fragmentColor * texture2D(tex_fore, v_texCoord);"
    "}";
}

bool PaintProgram::addShader(SHADER_TYPE type,const char* code)
{
    PaintShader* obj = new PaintShader();
    obj->setType(type);
    if(!obj->compileShaderCode(code))
    {
        delete obj;
        return false;
    }
    m_shaders.push_back(obj);
    PaintEngine::GetInstance()->attachShader(m_programId,obj->getId());
    return true;
}

bool PaintProgram::init()
{
    if(!initShader()){
        return false;
    }
    CHECK_GL_ERROR;
    initShaderAttrib();
    CHECK_GL_ERROR;
    if(!link()){
        return false;
    }
    bind();
    CHECK_GL_ERROR;
    return true;
}

bool PaintProgram::initShader()
{
    if(!addShader(SHADER_TYPE_VERTEX,getShader_V())) {
        return false;
    }
    if(!addShader(SHADER_TYPE_FRAGMENT,getShader_F())){
        return false;
    }
    return true;
}

bool PaintProgram::link()
{
    if(!PaintEngine::GetInstance()->linkProgram(m_programId)) {
        return false;
    }
    return true;
}




void PaintProgram::setUniformValue(const String& name,GLfloat value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        PaintEngine::GetInstance()->setUniform1f(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void PaintProgram::setUniformValue(const String& name,GLint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        PaintEngine::GetInstance()->setUniform1i(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void PaintProgram::setUniformValue(const String& name,GLuint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        PaintEngine::GetInstance()->setUniform1i(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void PaintProgram::setUniformValue(const String& name,const Size& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        float v[2];
        v[0] = value.width;
        v[1] = value.height;
        PaintEngine::GetInstance()->setUniform2fv(iter->second,2,(GLfloat*)&value);
    }
    CHECK_PROGRAM_ERROR(this);
}

void PaintProgram::setUniformValue(const String& name,const kmMat4& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        PaintEngine::GetInstance()->setUniformMatrix4fv(iter->second, 1,GL_FALSE,(GLfloat*)value.mat);
    }
    CHECK_PROGRAM_ERROR(this);
}

void PaintProgram::setUniformValue(const String& name, GLfloat* value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        PaintEngine::GetInstance()->setUniformMatrix4fv(iter->second, 1,GL_FALSE,value);
    }
    CHECK_PROGRAM_ERROR(this);
}

DE_END
