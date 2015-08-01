//
//  NormalProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "NormalProgram.h"

DE_BEGIN


NormalProgram::NormalProgram()
{
    
}

NormalProgram::~NormalProgram()
{
    
}

bool NormalProgram::init()
{
    GLShaderObject *vshader = new GLShaderObject();
    vshader->setType(SHADER_TYPE_VERTEX);
    const char *vsrc =
    "uniform mat4 matrix;"
    "attribute vec4 a_position;"
    "attribute vec2 a_texCoord;"
    "attribute vec4 a_color;"
    "\n#ifdef GL_ES\n"
    "varying lowp vec4 v_fragmentColor;"
    "varying mediump vec2 v_texCoord;"
    "\n#else\n"
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    "\n#endif\n"
    "void main()"
    "{"
        "gl_Position = matrix * a_position;"
        "v_fragmentColor = a_color;"
        "v_texCoord = a_texCoord;"
    "}";
    if(!vshader->compileShaderCode(vsrc)) {
        return false;
    }
    
    GLShaderObject *fshader = new GLShaderObject();
    fshader->setType(SHADER_TYPE_FRAGMENT);
    const char *fsrc =
    "#ifdef GL_ES\n"
    "precision lowp float;"
    "\n#endif\n"
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    "uniform sampler2D tex_fore;"
    "void main()"
    "{"
        "gl_FragColor = v_fragmentColor * texture2D(tex_fore, v_texCoord);"
    "}";
    if(!fshader->compileShaderCode(fsrc)) {
        return false;
    }
    
    addShader(vshader);
    addShader(fshader);
    
    link();
    
    bind();
    return true;
}

void NormalProgram::actived(PaintConfig& config)
{
    if (config.scale9) {
        activedWithScale9(config);
        return;
    }
    
    GLDrawData quad;
    quad.setPos(0, 0, config.width, config.height,config.trans);
    quad.setStart(config.start);
    if (config.end) {
        quad.setEnd(config.end);
    }
    else {
        quad.setEnd(config.start);
    }
    const Rect& rect = config.frame->getRect();
    if (config.flipY) {
        quad.setFrameRect(rect.x/config.frame->getTexture()->getWidth(),
                          (rect.y+rect.height)/config.frame->getTexture()->getHeight(),
                          (rect.x+rect.width)/config.frame->getTexture()->getWidth(),
                          rect.y/config.frame->getTexture()->getHeight());
    }
    else {
        quad.setFrameRect(rect.x/config.frame->getTexture()->getWidth(),
                          rect.y/config.frame->getTexture()->getHeight(),
                          (rect.x+rect.width)/config.frame->getTexture()->getWidth(),
                          (rect.y+rect.height)/config.frame->getTexture()->getHeight());
    }
    m_quads.push_back(quad);
    draw();
}

void NormalProgram::activedWithScale9(PaintConfig& config)
{
    GLDrawData quad;
    float frameW = config.frame->getWidth();
    float frameH = config.frame->getHeight();
    float vx[] = {
        0,
        frameW*config.scale9->l,
        config.width - frameW*(config.scale9->r)
    };
    float vy[] = {
        0,
        frameH*config.scale9->b,
        config.height - frameH*(config.scale9->t)
    };
    float vw[] = {
        frameW*config.scale9->l,
        config.width - frameW*(config.scale9->r+config.scale9->l),
        frameW*config.scale9->r
    };
    float vh[] = {
        frameH*config.scale9->b,
        config.height - frameH*(config.scale9->b+config.scale9->t),
        frameH*config.scale9->t
    };
    float fw [] = {
        0,1-config.scale9->l,
        config.scale9->l,config.scale9->r,
        1-config.scale9->r,0
    };
    float fh [] = {
        0,1-config.scale9->b,
        config.scale9->b,config.scale9->t,
        1-config.scale9->t,0
    };
    for (int i=0; i<9; ++i) {
        int iw = i%3;
        int ih = i/3;
        quad.setPos(vx[iw], vy[ih], vw[iw], vh[ih],config.trans);
        quad.setStart(config.start);
        quad.setEnd(config.start);
        const Rect& rect = config.frame->getRect();
        quad.setFrameRect(rect.x/config.frame->getTexture()->getWidth(),
                          rect.y/config.frame->getTexture()->getHeight(),
                          rect.width/config.frame->getTexture()->getWidth(),
                          rect.height/config.frame->getTexture()->getHeight());
        quad.setInnerRect(fw[iw*2], fw[iw*2+1], fh[ih*2], fh[ih*2+1]);
        m_quads.push_back(quad);
    }
    draw();
}

DE_END