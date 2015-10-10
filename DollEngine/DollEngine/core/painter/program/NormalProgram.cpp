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
    const char *vsrc = getShader_V();
    if(!vshader->compileShaderCode(vsrc)) {
        CHECK_GL_ERROR;
        return false;
    }
    
    GLShaderObject *fshader = new GLShaderObject();
    fshader->setType(SHADER_TYPE_FRAGMENT);
    const char *fsrc = getShader_F();
    if(!fshader->compileShaderCode(fsrc)) {
        CHECK_GL_ERROR;
        return false;
    }
    
    addShader(vshader);
    addShader(fshader);
    
    DI->linkProgram(m_programId);
    
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
