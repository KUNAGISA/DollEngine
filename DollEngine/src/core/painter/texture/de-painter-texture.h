//
//  de-painter-texture.h
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_painter_texture__
#define __DollEngine__de_painter_texture__

#include "de-functions.h"
#include "de-painter-image.h"

NAMESPACE_DE_PAINTER

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();
    bool initWithImage(Image* image);
    
    void retain();
    void release();
public:
    PROPERTY(bool, AutoRelease, m_autoRelease){m_autoRelease=v;}
    PROPERTY(GLuint, TexId, m_texId){m_texId=v;}
    PROPERTY(int, Width, m_width){m_width=v;}
    PROPERTY(int, Height, m_height){m_height=v;}
    PROPERTY(int, RetainCount, m_retainCount){m_retainCount=v;}
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_painter_texture__) */
