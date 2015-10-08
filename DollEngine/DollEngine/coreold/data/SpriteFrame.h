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

DE_BEGIN

class SpriteFrame
{
public:
    SpriteFrame();
    ~SpriteFrame();
    void retain();
    void release();
    void saveRect(){m_orginRect = m_rect;}
    float getOrginWidth(){return m_orginRect.width;}
    float getOrginHeight(){return m_orginRect.height;}
    
    void setWidth(float v){m_rect.width=v;}
    float getWidth(){return m_rect.width;}
    void setHeight(float v){m_rect.height=v;}
    float getHeight(){return m_rect.height;}
    
    GLfloat* getGLCoord(){return m_glCoord;}
    PROPERTY(GLTexture*,Texture,m_texture);
    void setRect(const Rect& v);
    const Rect& getRect(){return m_rect;}
    PROPERTY_CONST(string,CacheKey,m_cacheKey){m_cacheKey=v;}
    PROPERTY_RO(int,RetainCount,m_retainCount)
protected:
    GLfloat m_glCoord[8];
    void* m_otherData;
    Rect m_rect;
    Rect m_orginRect;
};
DE_END


#endif /* defined(__DollEngine__SpriteFrame__) */
