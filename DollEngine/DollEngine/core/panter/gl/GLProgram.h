//
//  GLProgram.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLProgram__
#define __DollEngine__GLProgram__

#include "Units.h"
#include "GLShaderObject.h"
#include "Transform.h"
#include "SpriteFrame.h"
#include "GLFunctions.h"

DE_BEGIN
enum {
    VERTEX_ATTRIB_FLAG_NONE       = 0,
    
    VERTEX_ATTRIB_FLAG_POSITION   = 1 << 0,
    VERTEX_ATTRIB_FLAG_COLOR      = 1 << 1,
    VERTEX_ATTRIB_FLAG_TEX_COORD = 1 << 2,
    
    VERTEX_ATTRIB_FLAG_POS_COLOR_TEX = (VERTEX_ATTRIB_FLAG_POSITION | VERTEX_ATTRIB_FLAG_COLOR | VERTEX_ATTRIB_FLAG_TEX_COORD),
};

enum PROGRAM_ATTRIBUTE
{
    PROGRAM_VERTEX_ATTRIBUTE=0,
    PROGRAM_COLOR_ATTRIBUTE,
    PROGRAM_TEXCOORD_ATTRIBUTE,
    PROGRAM_OPACITY_ATTRIBUTE,
    PROGRAM_TEXTURE_ATTRIBUTE,
    PROGRAM_FBO_ATTRIBUTE,
    PROGRAM_MATRIX_ATTRIBUTE,
};

enum PROGRAM_TYPE
{
    NORMAL_PROGRAM = 0,//正常模式
    CROSSFADE_PROGRAM = 1,//trans中使用的crossfade模式
};

class GLProgram
{
public:
    GLProgram();
    ~GLProgram();
    void addShader(SHADER_TYPE type,const char* code);
    void addShader(GLShaderObject* obj);
    bool bind();
    void bindAttributeLocation(const char * name, int location);
    bool link();
    void use();
    void enableVertexAttribs(uint32_t flags);
public:
    void setUniformValue(const char* name,GLfloat value);
    void setUniformValue(const char* name,GLint value);
    void setUniformValue(const char* name,GLuint value);
    void setUniformValue(const char* name,const kmMat4& value);
    
public:
    PROPERTY_RO(GLuint, ProgramId, m_programId)
    
    virtual bool init(){return false;}
    virtual void actived(SpriteFrame*,Transform*,GradientColor*){}
private:
    vector<GLShaderObject*> m_shaders;
    map<const char*, GLint> m_allUniformIndex;

};

DE_END

#endif /* defined(__DollEngine__GLProgram__) */
