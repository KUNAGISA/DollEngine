//
//  GLCanvas.cpp
//  DEPainter
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLCanvas.h"
#include "Application.h"

DE_BEGIN

GLCanvas::GLCanvas()
:m_layerHeight(0)
,m_layerWidth(0)
,m_layerX(0)
,m_layerY(0)
,m_layerZoom(0)
,m_initialized(false)
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
        float layerWidth = getLayerWidth();
        float layerHeight = getLayerHeight();
        float deviceWidth = DEApplication->getDeviceWidth();
        float deviceHeight = DEApplication->getDeviceHeight();
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
        m_globalTrans->setY(layerY*2/deviceHeight-1);
        m_globalTrans->setScaleX(2/deviceWidth * layerZoom);
        m_globalTrans->setScaleY(2/deviceHeight * layerZoom);
        m_globalTrans->flush();
        
        setLayerX(layerX);
        setLayerY(layerY);
        
        setLayerZoom(layerZoom);
#ifdef OS_MAC
        glViewport(0,0,deviceWidth,deviceHeight);
        glOrtho(-1, 1, -1, 1, -1, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
#endif
        NEED_REDRAW;
    }
}

DE_END