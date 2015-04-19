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
}

PaintEngine::~PaintEngine()
{
    
}

void PaintEngine::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    
    
    glDisable(GL_DEPTH_TEST);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    GL::blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    CHECK_GL_ERROR;
    initPrograms();
    
    GL::setProjectionMatrixDirty();
    m_isInited = true;
}

void PaintEngine::clearGL()
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PaintEngine::resizeGL(int width, int height)
{
    if (m_isInited) {
        glViewport(0,0, width, height);
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

SpriteFrame* PaintEngine::addImage(const string& picKey,const string& plist)
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
            GLImage image;
            if(image.loadImages(file.absolutePath()))
            {
                tex = new GLTexture();
                tex->initWithImage(&image);
            }
            else {
                throw Debug::throwMsg(ERROR_IMAGE_LOAD_FAILD,picKey);
            }
            m_allTextures[file.absolutePath()] = tex;
            tex->setCacheKey(file.absolutePath());
            tex->retain();
        }
        
        SpriteFrame* frame = new SpriteFrame();
        frame->setTexture(tex);
        
        m_allSpriteFrames[file.absolutePath()] = frame;
        frame->setCacheKey(file.absolutePath());
        frame->retain();
        return frame;
    }
    else {
//        string fullPath = Storages::GetInstance()->getFullPath(plist);
        throw Debug::throwMsg("暂时不支持Plist格式");
        return null;
    }
}

void PaintEngine::draw(SpriteFrame* frame,Transform* trans,GradientColor* color,GLProgram* program)
{
    if (frame->getTexture()->getTextureId()==0) {
        return;
    }
//    m_vbo.destroy();
//    m_vbo.create();
//    m_vbo.bind();
//    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
//    
    program->setUniformValue("matrix", trans->getMatrix());
    program->actived(frame,trans,color);
    
    frame->getTexture()->bind();
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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