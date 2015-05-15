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

DE_BEGIN


class GLProgram
{
public:
    GLProgram();
    ~GLProgram();
    void addShader(SHADER_TYPE type,const char* code);
    void addShader(GLShaderObject* obj);
    bool bind();
    bool link();
    void use();
public:
    void bindVAO(GLuint vaoId);
    void enableVertexAttribs(uint32_t flags);
    void bindAttributeLocation(const char * name, int location);
    void setUniformValue(const char* name,GLfloat value);
    void setUniformValue(const char* name,GLint value);
    void setUniformValue(const char* name,GLuint value);
    void setUniformValue(const char* name,const kmMat4& value);
    
public:
    PROPERTY_RO(GLuint, ProgramId, m_programId)
    
    virtual bool init(){return false;}
    virtual void actived(SpriteFrame*,Transform*,Color*,bool isFlipY=false){}
private:
    vector<GLShaderObject*> m_shaders;
    map<const char*, GLint> m_allUniformIndex;

};

DE_END

#endif /* defined(__DollEngine__GLProgram__) */
