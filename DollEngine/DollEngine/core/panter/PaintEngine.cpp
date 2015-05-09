//
//  PaintEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "PaintEngine.h"
#include "NormalProgram.h"
#include "GLFunctions.h"
#include "FileInfo.h"
#include "Debug.h"
#include "GLImage.h"

DE_BEGIN

PaintEngine::PaintEngine()
:m_isInited(false)
{
    m_globalTrans = new Transform();
}

PaintEngine::~PaintEngine()
{
    delete m_globalTrans;
}

void PaintEngine::initializeGL()
{
    if (!m_isInited) {
        glEnable(GL_TEXTURE_2D);
        
        
        glDisable(GL_DEPTH_TEST);
        glClearColor(1,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        GL::blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
        CHECK_GL_ERROR;
        initPrograms();
        
        GL::setProjectionMatrixDirty();
        m_isInited = true;
        resizeGL();
    }
}

void PaintEngine::clearGL()
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PaintEngine::resizeGL()
{
    if (m_isInited) {
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
//            m_globalTrans->setX(0);
//            m_globalTrans->setY(0);
//            m_globalTrans->setScaleX(1/deviceWidth);
//            m_globalTrans->setScaleY(1/deviceHeight);
            m_globalTrans->flush();
            
            
#ifdef OS_MAC
            glViewport(0,0,deviceWidth,deviceHeight);
            glOrtho(-1, 1, -1, 1, -1, 1);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
#endif
        }
    }
}

void PaintEngine::initPrograms()
{
    if (m_allPrograms.size() == 0) {
        auto effect = new NormalProgram();
        addProgram(NORMAL_PROGRAM,effect);
    }
}

void PaintEngine::addProgram(PROGRAM_TYPE pm,GLProgram* effect)
{
    if(effect->init()) {
        m_allPrograms[pm] = effect;
    }
    else {
        delete effect;
    }
}

GLProgram* PaintEngine::getProgram(PROGRAM_TYPE pm)
{
    initPrograms();
    return m_allPrograms[pm];
}

GLTexture* PaintEngine::addTexture(const string& picKey)
{
    FileInfo file(picKey);
    if (!file.exist()) {
        throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
    }
    auto iter2 = m_allTextures.find(file.absolutePath());
    GLTexture* tex=null;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        GLImage image;
        if(image.loadImages(file.absolutePath()))
        {
            tex = new GLTexture();
            tex->initWithImage(&image);
        }
        else {
            throw Debug::throwMsg(ERROR_IMAGE_LOAD_FAILD,picKey);
            return null;
        }
        m_allTextures[file.absolutePath()] = tex;
        tex->setCacheKey(file.absolutePath());
        tex->retain();
    }
    return tex;
}

SpriteFrame* PaintEngine::addFrame(const string& picKey,const string& plist)
{
    if (plist == "") {
        FileInfo file(picKey);
        if (!file.exist()) {
            throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
        }
        auto iter = m_allSpriteFrames.find(file.absolutePath());
        if (iter != m_allSpriteFrames.end()) {
            return iter->second;
        }
        auto iter2 = m_allTextures.find(file.absolutePath());
        GLTexture* tex=null;
        if(iter2 != m_allTextures.end()) {
            tex = iter2->second;
        }
        else {
            tex = addTexture(picKey);
        }
        SpriteFrame* frame = new SpriteFrame();
        frame->setTexture(tex);
        
        m_allSpriteFrames[file.absolutePath()] = frame;
        frame->setCacheKey(file.absolutePath());
        frame->retain();
        return frame;
    }
    else {
        throw Debug::throwMsg("暂时不支持Plist格式");
        return null;
    }
}

void PaintEngine::paint(SpriteFrame* frame,Transform* trans,Color* color,GLProgram* program)
{
    if (frame &&
        frame->getTexture() &&
        frame->getTexture()->getTextureId() != 0)
    {
        program->use();
        program->setUniformValue("matrix", trans->getMatrix());
        
        GL::blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
        frame->getTexture()->bind(GL_TEXTURE0);
        
        program->actived(frame,trans,color);
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        CHECK_GL_ERROR;
//        unsigned char* data = frame->getTexture()->getData();
//        delete data;
    }
}

void PaintEngine::removeSpriteFrameCache(SpriteFrame* frame)
{
    m_allSpriteFrames.erase(frame->getCacheKey());
}

void PaintEngine::removeTextureCache(GLTexture* frame)
{
    m_allTextures.erase(frame->getCacheKey());
}

DE_END