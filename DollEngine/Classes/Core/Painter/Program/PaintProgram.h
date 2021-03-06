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

class PaintEngine;
class PaintProgram
{
public:
    PaintProgram();
    virtual ~PaintProgram();
    virtual const char* getShader_V();
    virtual const char* getShader_F();
    virtual bool init();
    virtual bool initShader();
    virtual void initShaderAttrib(){}
    virtual bool link();
    virtual void bind(){}
    virtual void preparePaint(PaintConfig& config){}
public:
    bool addShader(SHADER_TYPE type,const char* code);
    size_t getShaderCount(){return m_shaders.size();}
    PaintShader* getShader(int idx){return m_shaders[idx];}
    void setUniformValue(const String& name,GLfloat value);
    void setUniformValue(const String& name,GLint value);
    void setUniformValue(const String& name,GLuint value);
    void setUniformValue(const String& name,const Size& value);
    void setUniformValue(const String& name,const kmMat4& value);
    void setUniformValue(const String& name, GLfloat* value);
    
public:
    PROPERTY_RO(GLuint, ProgramId, m_programId)
protected:
    vector<PaintShader*> m_shaders;
    map<String, GLint> m_allUniformIndex;
    PaintEngine* m_engine;
    
//    GLuint              m_pBuffersVBO[2]; //0: vertex  1: indices
//    vector<GLushort>           m_pIndices;
//    GLuint              m_uVAOname;
};

DE_END

#endif /* defined(__DollEngine__PaintProgram__) */
