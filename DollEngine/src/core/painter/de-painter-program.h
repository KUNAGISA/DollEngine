//
//  de-painter-program.h
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_painter_program__
#define __DollEngine__de_painter_program__

#include "de-functions.h"
#include "de-painter-shaderobject.h"

NAMESPACE_DE_PAINTER

class Program
{
public:
    Program();
    ~Program();
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

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_painter_program__) */
