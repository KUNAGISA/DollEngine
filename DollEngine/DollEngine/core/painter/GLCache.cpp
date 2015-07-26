//
//  GLCache.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLCache.h"
#include "Transform.h"
#include "TextFrame.h"
#include "GLProgram.h"
#include "FileInfo.h"
#include "Debug.h"
#include "FontCache.h"

DE_BEGIN

GLCache::GLCache()
{
}

TextFrame* GLCache::addText(const string& text,const string& fontName,int fontSize)
{
    string _fontName;
    if (fontName.empty() || text == "") {
        _fontName = DEFFONT;
    }
    else {
        _fontName = fontName;
    }
    
    if (fontSize == 0 || text == "") {
        fontSize = DEFFONTSIZE;
    }
    
    string key = FontCache::GetKeyByFont(text,fontName,fontSize,0);
    
    auto iter = m_allSpriteFrames.find(key);
    if (iter != m_allSpriteFrames.end()) {
        return dynamic_cast<TextFrame*>(iter->second);
    }
    
    TextFrame* frame = new TextFrame();
    GLTexture* tex= null;
    auto iter2 = m_allTextures.find(key);
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        
        FontData* fd = new FontData();
        
        ImageData* image = FontCache::GetInstance()->addText(text, fontName, fontSize,fd);
        
        tex = new GLTexture();
        if(tex->initWithImage(image)) {
            delete image;
        }
        else {
            delete image;
            delete tex;
            delete frame;
            delete fd;
            return null;
        }
        frame->setFont(fd);
    }

    frame->setTexture(tex);
    
    m_allSpriteFrames[key] = frame;
    frame->setCacheKey(key);
    frame->retain();
    return frame;
}

GLTexture* GLCache::addTexture(const string& picKey)
{
    FileInfo file(picKey);
    if (!file.exist()) {
        Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
    }
    auto iter2 = m_allTextures.find(file.absolutePath());
    GLTexture* tex=null;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        ImageData image;
        if(image.loadImages(file.absolutePath()))
        {
            tex = new GLTexture();
            tex->initWithImage(&image);
        }
        else {
            Debug::throwMsg(ERROR_IMAGE_LOAD_FAILD,picKey);
            return null;
        }
        m_allTextures[file.absolutePath()] = tex;
        tex->setCacheKey(file.absolutePath());
        tex->retain();
    }
    return tex;
}

SpriteFrame* GLCache::addFrame(const string& picKey,const string& plist)
{
    if (plist == "") {
        FileInfo file(picKey);
        if (!file.exist()) {
            Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
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
        Debug::throwMsg("暂时不支持Plist格式");
        return null;
    }
}

GLTexture* GLCache::addTexture(int r)
{
    string pickKey = Utf8WithFormat("round%d",r);
    auto iter2 = m_allTextures.find(pickKey);
    GLTexture* tex=null;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        tex = new GLTexture();
        ImageData* image = ImageData::createRoundRect(r);
        tex->initWithImage(image);
        delete image;
        m_allTextures[pickKey] = tex;
        tex->setCacheKey(pickKey);
        tex->retain();
    }
    return tex;
}//创建圆角矩形

SpriteFrame* GLCache::addFrame(int r)
{
    string pickKey = Utf8WithFormat("round%d",r);
    auto iter = m_allSpriteFrames.find(pickKey);
    if (iter != m_allSpriteFrames.end()) {
        return iter->second;
    }
    auto iter2 = m_allTextures.find(pickKey);
    GLTexture* tex=null;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        tex = addTexture(r);
    }
    SpriteFrame* frame = new SpriteFrame();
    frame->setTexture(tex);
    
    m_allSpriteFrames[pickKey] = frame;
    frame->setCacheKey(pickKey);
    frame->retain();
    return frame;
    
}//创建圆角矩形

void GLCache::removeSpriteFrameCache(SpriteFrame* frame)
{
    m_allSpriteFrames.erase(frame->getCacheKey());
}

void GLCache::removeTextureCache(GLTexture* frame)
{
    m_allTextures.erase(frame->getCacheKey());
}

DE_END