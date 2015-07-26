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

struct PaintConfig
{
    SpriteFrame* frame;
    Transform* trans;
    Color* color;
    int gradVector;//渐变方向
    Color* end;
    GLProgram* program;
    float width;
    float height;
    GLenum blendSrc;
    GLenum blendDst;
};

class GLPainter
{
public:
    
    GLPainter();
    Shared(GLPainter)
    virtual ~GLPainter();
    
public:
    void blendFunc(GLenum src,GLenum dst);
    void addProgram(string pm,GLProgram*);
    GLProgram* getProgram(string pm);
    
public:
    void paint(PaintConfig& config);
protected:
    map<string,GLProgram*> m_allPrograms;
};

DE_END


#endif /* defined(__DollEngine__GLPainter__) */
