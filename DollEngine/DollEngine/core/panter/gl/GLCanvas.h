//
//  GLCanvas.h
//  DollEngine
//
//  Created by DollStudio on 15/5/10.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLCanvas__
#define __DollEngine__GLCanvas__

#include "Units.h"

DE_BEGIN

class SpriteFrame;
class GLTexture;
class GLProgram;
class Transform;
enum PROGRAM_TYPE;

class GLCanvas
{
public:
    
    GLCanvas();
    Shared(GLCanvas)
    virtual ~GLCanvas();
    
    void initializeGL();
    void clearGL();
    void resizeGL();
    
public:
    void initPrograms();
    void addProgram(PROGRAM_TYPE pm,GLProgram*);
    GLProgram* getProgram(PROGRAM_TYPE pm);
    
public:
    PROPERTY_RO(Transform*,GlobalTrans,m_globalTrans)
public:
    void paint(SpriteFrame* frame,Transform* trans,Color* color,GLProgram* program);
protected:
    map<PROGRAM_TYPE,GLProgram*> m_allPrograms;
    bool m_initialized;
};

DE_END


#endif /* defined(__DollEngine__GLCanvas__) */
