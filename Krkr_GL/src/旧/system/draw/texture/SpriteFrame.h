//
//  SpriteFrame.h
//  Krkr_GL
//
//  Created by DollStudio on 14-9-19.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__SpriteFrame__
#define __Krkr_GL__SpriteFrame__

#include "Texture2D.h"

class SpriteFrame
{
public:
    SpriteFrame();
    ~SpriteFrame();
    
    bool initWithTexture(Texture2D* tex,const kRect& rect);
    bool initWithTexture(Texture2D* tex);
    float getWidth();
    float getHeight();
    GLfloat* getGLCoord(){return m_glCoord;}
    void retain();
    void release();
public:
    PROPERTY(Texture2D*, Texture, m_texture);
    PROPERTY(kRect, Rect, m_rect);
    PROPERTY(uint, RetainCount, m_retainCount){m_retainCount=v;}
    
protected:
    GLfloat m_glCoord[8];
};

#endif /* defined(__Krkr_GL__SpriteFrame__) */
