//
//  GLCanvas.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/10.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLCanvas.h"
#include "Transform.h"
#include "SpriteFrame.h"
#include "GLProgram.h"
#include "NormalProgram.h"
#include "FileInfo.h"
#include "Debug.h"
#include "GLImage.h"

DE_BEGIN

GLCanvas::GLCanvas()
:m_initialized(false)
{
    m_globalTrans = new Transform();
}

GLCanvas::~GLCanvas()
{
    delete m_globalTrans;
}

void GLCanvas::initializeGL()
{
    if (!m_initialized) {
        m_initialized = true;
        glEnable(GL_TEXTURE_2D);
        
        
        glDisable(GL_DEPTH_TEST);
        
        clearGL();
        
        CHECK_GL_ERROR;
        
        initPrograms();
        
        resizeGL();
    }
}

void GLCanvas::clearGL()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLCanvas::resizeGL()
{
    if (m_initialized) {
        if (Device::GetInstance()->getCurrentCanvas()) {
            float layerWidth = Device::GetInstance()->getCurrentCanvas()->getLayerWidth();
            float layerHeight = Device::GetInstance()->getCurrentCanvas()->getLayerHeight();
            float deviceWidth = Device::GetInstance()->getDeviceWidth();
            float deviceHeight = Device::GetInstance()->getDeviceHeight();
            float p = layerWidth/layerHeight;
            float sc_p = deviceWidth/deviceHeight;
            float layerZoom = 1, layerX = 0, layerY = 0;
            if (p > sc_p) {
                //上下留边
                layerZoom = deviceWidth/layerWidth;
                layerX = 0;
                layerY = (deviceHeight - layerHeight*layerZoom)/2;
            }
            else {
                //左右留边
                layerZoom = deviceHeight/layerHeight;
                layerX = (deviceWidth - layerWidth * layerZoom)/2;
                layerY = 0;
            }
            
            m_globalTrans->setX(layerX*2/deviceWidth-1);
            m_globalTrans->setY(-layerY*2/deviceHeight+1);
            m_globalTrans->setScaleX(2/deviceWidth * layerZoom);
            m_globalTrans->setScaleY(-2/deviceHeight * layerZoom);
            m_globalTrans->flush();
            
            Device::GetInstance()->getCurrentCanvas()->setLayerLeft(layerX);
            Device::GetInstance()->getCurrentCanvas()->setLayerTop(layerY);
            
            Device::GetInstance()->getCurrentCanvas()->setLayerZoom(layerZoom);
#ifdef OS_MAC
            glViewport(0,0,deviceWidth,deviceHeight);
            glOrtho(-1, 1, -1, 1, -1, 1);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
#endif
            NEED_REDRAW;
        }
    }
}

void GLCanvas::initPrograms()
{
    if (m_allPrograms.size() == 0) {
        auto effect = new NormalProgram();
        addProgram(NORMAL_PROGRAM,effect);
    }
}

void GLCanvas::addProgram(PROGRAM_TYPE pm,GLProgram* effect)
{
    if(effect->init()) {
        m_allPrograms[pm] = effect;
    }
    else {
        delete effect;
    }
}

GLProgram* GLCanvas::getProgram(PROGRAM_TYPE pm)
{
    initPrograms();
    return m_allPrograms[pm];
}

void GLCanvas::paint(SpriteFrame* frame,Transform* trans,Color* color,GLProgram* program)
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
