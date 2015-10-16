//
//  GLProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLProgram.h"
#include "PaintEngine.h"

DE_BEGIN

GLProgram::GLProgram()
{
    m_programId = PaintEngine::GetInstance()->createProgram();
}

GLProgram::~GLProgram()
{
    for (GLShaderObject* obj : m_shaders)
    {
        PaintEngine::GetInstance()->detachShader(m_programId,obj->getId());
        delete obj;
    }
    m_shaders.clear();
    PaintEngine::GetInstance()->deleteProgram(m_programId);
}

const char* GLProgram::getShader_V()
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

const char* GLProgram::getShader_F()
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
    PaintEngine::GetInstance()->attachShader(m_programId,obj->getId());
}

bool GLProgram::bind()
{
    PaintEngine::GetInstance()->bindAttribute(m_programId, "a_position",PROGRAM_VERTEX_ATTRIBUTE);
    PaintEngine::GetInstance()->bindAttribute(m_programId,"a_color",PROGRAM_COLOR_ATTRIBUTE);
    PaintEngine::GetInstance()->bindAttribute(m_programId,"a_texCoord",PROGRAM_TEXCOORD_ATTRIBUTE);
    //    bind(PROGRAM_OPACITY_ATTRIBUTE,"a_opacity");
    if(!PaintEngine::GetInstance()->linkProgram(m_programId))
    {
        return false;
    }
    PaintEngine::GetInstance()->bindAttribute(m_programId,"tex_fore",PROGRAM_TEXTURE_ATTRIBUTE);
    PaintEngine::GetInstance()->bindAttribute(m_programId,"tex_back",PROGRAM_TEXTURE_ATTRIBUTE);
    PaintEngine::GetInstance()->bindAttribute(m_programId,"texture_fbo",PROGRAM_FBO_ATTRIBUTE);
    PaintEngine::GetInstance()->bindAttribute(m_programId,"matrix",PROGRAM_MATRIX_ATTRIBUTE);
    
    int index = PaintEngine::GetInstance()->getUniform(m_programId,"tex_fore");
    if (index != -1) m_allUniformIndex["tex_fore"]=index;
    
    index = PaintEngine::GetInstance()->getUniform(m_programId,"tex_back");
    if (index != -1) m_allUniformIndex["tex_back"]=index;
    
    index = PaintEngine::GetInstance()->getUniform(m_programId, "texture_fbo");
    if (index != -1) m_allUniformIndex["texture_fbo"]=index;
    
    index = PaintEngine::GetInstance()->getUniform(m_programId,"matrix");
    if (index != -1) m_allUniformIndex["matrix"]=index;
    
    PaintEngine::GetInstance()->useProgram(m_programId);
    setUniformValue("tex_fore",0);
    CHECK_GL_ERROR;
    return true;
}



void GLProgram::setUniformValue(const char* name,GLfloat value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        PaintEngine::GetInstance()->setUniform1f(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,GLint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        PaintEngine::GetInstance()->setUniform1i(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,GLuint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        PaintEngine::GetInstance()->setUniform1i(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,const Size& value)
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

void GLProgram::setUniformValue(const char* name,const kmMat4& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        PaintEngine::GetInstance()->setUniformMatrix4fv(iter->second, 1,GL_FALSE,(GLfloat*)value.mat);
    }
    CHECK_PROGRAM_ERROR(this);
}


void GLProgram::draw()
{
    if (m_quads.size() == 0) {
        return;
    }
    PaintEngine::GetInstance()->bindVAO(0);
    
#define kQuadSize sizeof(GLVertex)
    long offset = (long)m_quads.data();
    PaintEngine::GetInstance()->enableVertexAttribs(VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    int diff = offsetof( GLVertex, vertex);
    PaintEngine::GetInstance()->vertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    diff = offsetof( GLVertex, color);
    PaintEngine::GetInstance()->vertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    diff = offsetof( GLVertex, uv);
    PaintEngine::GetInstance()->vertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, kQuadSize,(void*) (offset + diff));
    int size = (int)m_quads.size()*4;
    
    for (int i=0; i<m_quads.size(); ++i) {
        m_indexs.push_back(i*4);
        m_indexs.push_back(i*4+1);
        m_indexs.push_back(i*4+2);
        m_indexs.push_back(i*4+2);
        m_indexs.push_back(i*4+3);
        m_indexs.push_back(i*4);
    }
    PaintEngine::GetInstance()->drawElements(GL_TRIANGLES, m_quads.size()*2*3, GL_UNSIGNED_SHORT, m_indexs.data());
//    glDrawArrays(GL_TRIANGLE_FAN, 0, size);
    
    CHECK_GL_ERROR;
    m_quads.clear();
    m_indexs.clear();
}

DE_END
