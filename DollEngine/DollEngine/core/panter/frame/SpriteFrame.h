//
//  SpriteFrame.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__SpriteFrame__
#define __DollEngine__SpriteFrame__

#include "GLTexture.h"
#include "BaseComp.h"

DE_BEGIN

class SpriteFrame
{
public:
    SpriteFrame();
    ~SpriteFrame();
    void retain();
    void release();
    
    void setWidth(float v){m_rect.width=v;}
    float getWidth(){return m_rect.width;}
    void setHeight(float v){m_rect.height=v;}
    float getHeight(){return m_rect.height;}
    
    GLfloat* getGLCoord(){return m_glCoord;}
    PROPERTY(GLTexture*,Texture,m_texture);
    PROPERTY_CONST(Rect,Rect,m_rect);
    PROPERTY_CONST(string,CacheKey,m_cacheKey){m_cacheKey=v;}
    PROPERTY_RO(int,RetainCount,m_retainCount)
protected:
    GLfloat m_glCoord[8];
    void* m_otherData;
};
DE_END


#endif /* defined(__DollEngine__SpriteFrame__) */
