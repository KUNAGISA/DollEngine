//
//  GLTexture.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLTexture__
#define __DollEngine__GLTexture__

#include "Units.h"
#include "GLImage.h"

DE_BEGIN

class GLTexture
{
public:
    GLTexture();
    virtual ~GLTexture();
    
    bool initWithImage(GLImage* img);
    void retain();
    void release();
    void bind(GLenum activeId=GL_TEXTURE0);
    PROPERTY_RO(int,RetainCount,m_retainCount)
    PROPERTY_CONST(string,CacheKey,m_cacheKey){m_cacheKey=v;}
    PROPERTY(GLuint, TextureId, m_textureId);
    
    PROPERTY(int, Width, m_width){m_width=v;}
    PROPERTY(int, Height, m_height){m_height=v;}
};

DE_END

#endif /* defined(__DollEngine__GLTexture__) */
