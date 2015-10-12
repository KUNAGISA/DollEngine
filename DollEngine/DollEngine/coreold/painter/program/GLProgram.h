//
//  GLProgram.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLProgram__
#define __DollEngine__GLProgram__

#include "CoreUnits.h"
#include "GLShaderObject.h"
#include "Transform.h"
#include "SpriteFrame.h"

DE_BEGIN


class GLProgram
{
public:
    GLProgram();
    ~GLProgram();
    virtual const char* getShader_V();
    virtual const char* getShader_F();
    void addShader(SHADER_TYPE type,const char* code);
    void addShader(GLShaderObject* obj);
    virtual bool bind();
    bool link();
    void use();
public:
    size_t getShaderCount(){return m_shaders.size();}
    GLShaderObject* getShader(int idx){return m_shaders[idx];}
    void bindVAO(GLuint vaoId);
    void enableVertexAttribs(uint32_t flags);
    void bindAttributeLocation(const char * name, int location);
    void setUniformValue(const char* name,GLfloat value);
    void setUniformValue(const char* name,GLint value);
    void setUniformValue(const char* name,GLuint value);
    void setUniformValue(const char* name,const Size& value);
    void setUniformValue(const char* name,const kmMat4& value);
    
public:
    PROPERTY_RO(GLuint, ProgramId, m_programId)
    
    virtual bool init(){return false;}
    virtual void actived(PaintConfig& config){}
    virtual void draw();
protected:
    vector<GLShaderObject*> m_shaders;
    map<const char*, GLint> m_allUniformIndex;
    
    vector<GLDrawData> m_quads;
    vector<GLushort> m_indexs;
    
    GLuint              m_pBuffersVBO[2]; //0: vertex  1: indices
    vector<GLushort>           m_pIndices;
    GLuint              m_uVAOname;
};

DE_END

#endif /* defined(__DollEngine__GLProgram__) */