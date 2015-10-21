//
//  PaintProgram.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__PaintProgram__
#define __DollEngine__PaintProgram__

#include "CoreTypes.h"
#include "PaintShader.h"
#include "Transform.h"
#include "ImageInfo.h"

DE_BEGIN


class PaintProgram
{
public:
    PaintProgram();
    ~PaintProgram();
    virtual const char* getShader_V();
    virtual const char* getShader_F();
    void addShader(SHADER_TYPE type,const char* code);
    virtual bool bind();
public:
    size_t getShaderCount(){return m_shaders.size();}
    PaintShader* getShader(int idx){return m_shaders[idx];}
    void setUniformValue(const char* name,GLfloat value);
    void setUniformValue(const char* name,GLint value);
    void setUniformValue(const char* name,GLuint value);
    void setUniformValue(const char* name,const Size& value);
    void setUniformValue(const char* name,const kmMat4& value);
    
public:
    PROPERTY_RO(GLuint, ProgramId, m_programId)
    
    virtual bool init(){return false;}
    virtual void beforeDraw(PaintConfig& config){}
protected:
    vector<PaintShader*> m_shaders;
    map<const char*, GLint> m_allUniformIndex;
    
    
//    GLuint              m_pBuffersVBO[2]; //0: vertex  1: indices
//    vector<GLushort>           m_pIndices;
//    GLuint              m_uVAOname;
};

DE_END

#endif /* defined(__DollEngine__PaintProgram__) */
