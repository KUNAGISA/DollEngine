//
//  Texture2D.h
//  DollEngine
//
//  Created by DollStudio on 14-9-19.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Texture2D__
#define __DollEngine__Texture2D__

#include "Image.h"

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

#endif /* defined(__DollEngine__Texture2D__) */
