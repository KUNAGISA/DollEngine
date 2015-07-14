//
//  Painter.h
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Painter__
#define __DollEngine__Painter__

#include "BaseComp.h"
#include "SpriteFrame.h"
#include "GLTexture.h"
#include "Transform.h"
#include "GLProgram.h"

DE_BEGIN

class Painter : public BaseComp
{
public:
    Painter();
    ~Painter();
public:
    bool loadImages(const string& path,const string& plist="");
    virtual Size getPaintSize();
public:
    void update();
    void blendFunc(GLenum src,GLenum dst);
    void setColor(uint32_t color);
    void setOpacity(GLubyte o);
    PROPERTY(SpriteFrame*, DisplayFrame, m_displayFrame);
    PROPERTY(GLProgram*, Program, m_program){m_program=v;}
    PROPERTY_CONST(Color, Color, m_color){m_color=v;}
    PROPERTY_RO(float, Width, m_width);
    PROPERTY_RO(float, Height, m_height);
protected:
    Transform* m_transform;
    
};

DE_END

#endif /* defined(__DollEngine__Painter__) */
