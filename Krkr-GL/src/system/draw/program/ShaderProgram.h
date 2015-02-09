//
//  ShaderProgram.h
//  DollEngine
//
//  Created by DollStudio on 14-9-14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ShaderProgram__
#define __DollEngine__ShaderProgram__

#include "Functions.h"
#include "ShaderObject.h"

class ShaderProgram
{
public:
    
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
        PROGRAM_TYPE_DEFAULT=0
    };
public:
    ShaderProgram();
    ~ShaderProgram();
    void addShader(ShaderObject* object);
    void addShaderFromCode(ShaderObject::SHADER_TYPE type, const char* code);
    bool bind();
    void bindAttributeLocation(const char * name, int location);
    bool link();
    void use();
public:
    void setUniformValue(const char* name,GLfloat value);
    void setUniformValue(const char* name,GLint value);
    void setUniformValue(const char* name,GLuint value);
    void setUniformValue(const char* name,const kmMat4& value);
    
public:
    PROPERTY_RO(GLuint, ProgramId, m_programId)
    
private:
    list<ShaderObject*> m_shaders;
    map<const char*, GLint> m_allUniformIndex;
};

#endif /* defined(__DollEngine__ShaderProgram__) */
