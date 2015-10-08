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

static GLuint s_VAO=-1;
void GLProgram::bindVAO(GLuint vaoId)
{
    if (s_VAO != vaoId)
    {
        s_VAO = vaoId;
        glBindVertexArray(vaoId);
    }
}

static int MAX_ATTRIBUTES = 16;
static uint32_t s_attributeFlags = 0;
void GLProgram::enableVertexAttribs(uint32_t flags)
{
    
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
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,GLint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1i(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,GLuint value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
        glUniform1i(iter->second, value);
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,const Size& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        int v[2];
        v[0] = value.width;
        v[1] = value.height;
        glUniform2fv(iter->second,2,(GLfloat*)&value);
    }
    CHECK_PROGRAM_ERROR(this);
}

void GLProgram::setUniformValue(const char* name,const kmMat4& value)
{
    auto iter = m_allUniformIndex.find(name);
    if(iter != m_allUniformIndex.end())
    {
        glUniformMatrix4fv(iter->second, 1,GL_FALSE,(GLfloat*)value.mat);
    }
    CHECK_PROGRAM_ERROR(this);
}


void GLProgram::draw()
{
    if (m_quads.size() == 0) {
        return;
    }
    bindVAO(0);
    
#define kQuadSize sizeof(GLVertex)
    long offset = (long)m_quads.data();
    enableVertexAttribs(VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    int diff = offsetof( GLVertex, vertex);
    glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    diff = offsetof( GLVertex, color);
    glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    diff = offsetof( GLVertex, uv);
    glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, kQuadSize,(void*) (offset + diff));
    int size = (int)m_quads.size()*4;
    
    for (int i=0; i<m_quads.size(); ++i) {
        m_indexs.push_back(i*4);
        m_indexs.push_back(i*4+1);
        m_indexs.push_back(i*4+2);
        m_indexs.push_back(i*4+2);
        m_indexs.push_back(i*4+3);
        m_indexs.push_back(i*4);
    }
    glDrawElements(GL_TRIANGLES, m_quads.size()*2*3, GL_UNSIGNED_SHORT, m_indexs.data());
//    glDrawArrays(GL_TRIANGLE_FAN, 0, size);
    
    CHECK_GL_ERROR;
    m_quads.clear();
    m_indexs.clear();
}

DE_END