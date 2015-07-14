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

DE_BEGIN

GLPainter::GLPainter()
{
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

void GLPainter::paint(SpriteFrame* frame,Transform* trans,Color* color,GLProgram* program)
{
    if (frame &&
        frame->getTexture() &&
        frame->getTexture()->getTextureId() != 0)
    {
        program->use();
        program->setUniformValue("matrix", trans->getMatrix());
        
        frame->getTexture()->bind(GL_TEXTURE0);
        
        program->actived(frame,trans,color);
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        CHECK_GL_ERROR;
    }
}

DE_END
