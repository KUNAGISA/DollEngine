//
//  Texture.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Texture__
#define __DollEngine__Texture__

#include "CoreTypes.h"
#include "PictureData.h"

DE_BEGIN

class Texture
{
public:
    Texture();
    virtual ~Texture();
    
    bool initWithImage(PictureData* img);
    bool initWithSize(int w,int h);
    void retain();
    void release();
    void bind(GLenum activeId=GL_TEXTURE0);
    
    unsigned char* getData();
    PROPERTY_RO(int,RetainCount,m_retainCount)
    PROPERTY_CONST(String,CacheKey,m_cacheKey){m_cacheKey=v;}
    PROPERTY(GLuint, TextureId, m_textureId);
    
    PROPERTY(int, Width, m_width){m_width=v;}
    PROPERTY(int, Height, m_height){m_height=v;}
};

DE_END

#endif /* defined(__DollEngine__Texture__) */
