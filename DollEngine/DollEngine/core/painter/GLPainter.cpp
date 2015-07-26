//
//  GLCanvas.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/10.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLPainter.h"
#include "Transform.h"
#include "SpriteFrame.h"
#include "GLProgram.h"
#include "FileInfo.h"
#include "Debug.h"
#include "ImageData.h"
#include "Application.h"
#include "NormalProgram.h"

DE_BEGIN

GLPainter::GLPainter()
{
    addProgram("normal", new NormalProgram());
}

GLPainter::~GLPainter()
{
}

void GLPainter::addProgram(string pm,GLProgram* effect)
{
    if(effect->init()) {
        m_allPrograms[pm] = effect;
    }
    else {
        delete effect;
    }
}

GLProgram* GLPainter::getProgram(string pm)
{
    return m_allPrograms[pm];
}


static GLenum s_blendingSource = -1;
static GLenum s_blendingDest = -1;
void GLPainter::blendFunc(GLenum src,GLenum dst)
{
    if (src != s_blendingSource || dst != s_blendingDest)
    {
        s_blendingSource = src;
        s_blendingDest = dst;
        if (src == GL_ONE && dst == GL_ZERO)
        {
            glDisable(GL_BLEND);
        }
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(src, dst);
        }
    }
}

void GLPainter::paint(PaintConfig& config)
{
    SpriteFrame* frame = config.frame;
    if (frame &&
        frame->getTexture() &&
        frame->getTexture()->getTextureId() != 0)
    {
        config.program->use();
        config.program->setUniformValue("matrix", config.trans->getMatrix());
        
        frame->getTexture()->bind(GL_TEXTURE0);
        
        config.program->actived(config);
        
        CHECK_GL_ERROR;
    }
}

DE_END
