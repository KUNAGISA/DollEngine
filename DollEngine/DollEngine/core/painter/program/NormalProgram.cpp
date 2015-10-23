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

void NormalProgram::preparePaint(PaintConfig& config)
{
    config.info->getTexture()->bind();
    if (config.info->getIsScale9()) {
        preparePaintWithScale9(config);
        return;
    }
    
    GLDrawData quad;
    config.info->toDrawData(quad,config.trans,config.flipX,config.flipY);
    PaintEngine::GetInstance()->pushDrawData(quad);
}

void NormalProgram::preparePaintWithScale9(PaintConfig& config)
{
//    GLDrawData quad;
//    float frameW = config.info->getWidth();
//    float frameH = config.info->getHeight();
//    Scale9Config scale9 = config.info->getScale9();
//    Size drawSize = config.info->getPaintSize();
//    float vx[] = {
//        0,
//        frameW*scale9.l,
//        drawSize.width - frameW*scale9.r
//    };
//    float vy[] = {
//        0,
//        frameH*scale9.b,
//        drawSize.height - frameH*(scale9.t)
//    };
//    float vw[] = {
//        frameW*scale9.l,
//        drawSize.width - frameW*(scale9.r+scale9.l),
//        frameW*scale9.r
//    };
//    float vh[] = {
//        frameH*scale9.b,
//        drawSize.height - frameH*(scale9.b+scale9.t),
//        frameH*scale9.t
//    };
//    float fw [] = {
//        0,1-scale9.l,
//        scale9.l,scale9.r,
//        1-scale9.r,0
//    };
//    float fh [] = {
//        0,1-scale9.b,
//        scale9.b,scale9.t,
//        1-scale9.t,0
//    };
//    for (int i=0; i<9; ++i) {
//        int iw = i%3;
//        int ih = i/3;
//        DrawVertex vex = {vx[iw], vy[ih], vw[iw], vh[ih],config.trans};
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
