//
//  RTTCanvas.h
//  Krkr_GL
//
//  Created by DollStudio on 15/1/10.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__RTTCanvas__
#define __Krkr_GL__RTTCanvas__

#include "COM.h"
#include "SpriteFrame.h"
#include "ShaderProgram.h"

class RTTCanvas : public COM
{
    
public:
    RTTCanvas();
    ~RTTCanvas();
    
    virtual void render(Object* orginNode,float x,float y);
    
    void trigger();
    
    PROPERTY(float, Width, m_width){m_width=v;m_sizeChanged=true;}
    PROPERTY(float, Height, m_height){m_height=v;m_sizeChanged=true;}
    PROPERTY(ShaderProgram*, Program, m_program){m_program=v;}
    PROPERTY(float, Opacity, m_opacity){m_opacity=fminf(1,fmaxf(0,v));}
    PROPERTY(SpriteFrame*, SpriteFrame, m_spriteFrame){m_spriteFrame=v;}
    PROPERTY(bool, SizeChanged, m_sizeChanged){m_sizeChanged=v;}
protected:
    GLuint m_FBO;
    GLint m_lastFBO;
};

#endif /* defined(__Krkr_GL__RTTCanvas__) */
