//
//  PaintEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__PaintEngine__
#define __DollEngine__PaintEngine__

#include "Units.h"
#include "Transform.h"
#include "SpriteFrame.h"
#include "GLProgram.h"

DE_BEGIN

class PaintEngine
{
public:
    
    PaintEngine();
    Shared(PaintEngine)
    virtual ~PaintEngine();
    
    void initializeGL();
    void clearGL();
    void resizeGL(int width, int height);
    
public:
    void initPrograms();
    void addProgram(PROGRAM_TYPE pm,GLProgram*);
    GLProgram* getProgram(PROGRAM_TYPE pm);
    
public:
    SpriteFrame* addImage(const string& picKey,const string& plist="");
    void removeSpriteFrameCache(SpriteFrame* frame);
    void removeTextureCache(GLTexture* frame);
    
public:
    void draw(SpriteFrame* frame,Transform* trans,GradientColor* color,GLProgram* program);
protected:
    map<string,string > m_allPlist;
    map<string,SpriteFrame*> m_allSpriteFrames;
    map<string,GLTexture*> m_allTextures;
    map<PROGRAM_TYPE,GLProgram*> m_allPrograms;
    bool m_isInited;
};

DE_END

#endif /* defined(__DollEngine__PaintEngine__) */
