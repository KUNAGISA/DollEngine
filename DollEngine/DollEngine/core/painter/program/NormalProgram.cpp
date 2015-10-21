//
//  NormalProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "NormalProgram.h"
#include "PaintEngine.h"

DE_BEGIN


NormalProgram::NormalProgram()
{
    
}

NormalProgram::~NormalProgram()
{
    
}

bool NormalProgram::init()
{
    addShader(SHADER_TYPE_VERTEX,getShader_V());
    addShader(SHADER_TYPE_FRAGMENT,getShader_F());
    
    PaintEngine::GetInstance()->linkProgram(m_programId);
    
    bind();
    return true;
}

void NormalProgram::beforeDraw(PaintConfig& config)
{
    config.info->getTexture()->bind();
    if (config.info->getIsScale9()) {
        beforeDrawWithScale9(config);
        return;
    }
    
    GLDrawData quad;
    DrawVertex vex = {0, 0, config.info->getWidth(), config.info->getHeight(),config.trans};
    
    config.info->toDrawData(quad,vex,config.flipX,config.flipY);
    PaintEngine::GetInstance()->pushDrawData(quad);
}

void NormalProgram::beforeDrawWithScale9(PaintConfig& config)
{
//    GLDrawData quad;
//    float frameW = config.info->getWidth();
//    float frameH = config.info->getHeight();
//    float vx[] = {
//        0,
//        frameW*config.scale9->l,
//        config.width - frameW*(config.scale9->r)
//    };
//    float vy[] = {
//        0,
//        frameH*config.scale9->b,
//        config.height - frameH*(config.scale9->t)
//    };
//    float vw[] = {
//        frameW*config.scale9->l,
//        config.width - frameW*(config.scale9->r+config.scale9->l),
//        frameW*config.scale9->r
//    };
//    float vh[] = {
//        frameH*config.scale9->b,
//        config.height - frameH*(config.scale9->b+config.scale9->t),
//        frameH*config.scale9->t
//    };
//    float fw [] = {
//        0,1-config.scale9->l,
//        config.scale9->l,config.scale9->r,
//        1-config.scale9->r,0
//    };
//    float fh [] = {
//        0,1-config.scale9->b,
//        config.scale9->b,config.scale9->t,
//        1-config.scale9->t,0
//    };
//    for (int i=0; i<9; ++i) {
//        int iw = i%3;
//        int ih = i/3;
//        quad.setPos(vx[iw], vy[ih], vw[iw], vh[ih],config.trans);
//        quad.setStart(config.start);
//        quad.setEnd(config.start);
//        const Rect& rect = config.info->getOrginRect();
//        quad.setFrameRect(rect.x/config.info->getTexture()->getWidth(),
//                          rect.y/config.info->getTexture()->getHeight(),
//                          rect.width/config.info->getTexture()->getWidth(),
//                          rect.height/config.info->getTexture()->getHeight());
//        quad.setInnerRect(fw[iw*2], fw[iw*2+1], fh[ih*2], fh[ih*2+1]);
//        m_quads.push_back(quad);
//    }
}

DE_END
