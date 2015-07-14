//
//  GLPainter.h
//  DollEngine
//
//  Created by DollStudio on 15/5/10.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLPainter__
#define __DollEngine__GLPainter__

#include "CoreUnits.h"

DE_BEGIN

class SpriteFrame;
class GLTexture;
class GLProgram;
class Transform;
enum PROGRAM_TYPE;

class GLPainter
{
public:
    
    GLPainter();
    Shared(GLPainter)
    virtual ~GLPainter();
    
public:
    void addProgram(string pm,GLProgram*);
    GLProgram* getProgram(string pm);
    
public:
    void paint(SpriteFrame* frame,Transform* trans,Color* color,GLProgram* program);
protected:
    map<string,GLProgram*> m_allPrograms;
};

DE_END


#endif /* defined(__DollEngine__GLPainter__) */
