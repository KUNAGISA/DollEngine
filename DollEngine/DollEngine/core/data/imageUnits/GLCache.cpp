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
#include "System.h"

DE_BEGIN

GLCache::GLCache()
{
}

TextFrame* GLCache::addText(const String& text,const String& fontName,int fontSize)
{
    String _fontName;
    if (fontName.empty() || text.empty()) {
        _fontName = DEFFONT;
    }
    else {
        _fontName = fontName;
    }
    
    if (fontSize == 0 || text.empty()) {
        fontSize = DEFFONTSIZE;
    }
    
    String key = System::GetKeyByFont(text,fontName,fontSize,0);
    
    auto iter = m_allSpriteFrames.find(key);
    if (iter != m_allSpriteFrames.end()) {
        return dynamic_cast<TextFrame*>(iter->second);
    }
    
    TextFrame* frame = new TextFrame();
    GLTexture* tex= NULL;
    auto iter2 = m_allTextures.find(key);
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        
        FontData* fd = new FontData();
        
        ImageData* image = System::GetInstance()->addText(text, fontName, fontSize,fd);
        
        tex = new GLTexture();
        if(tex->initWithImage(image)) {
            delete image;
        }
        else {
            delete image;
            delete tex;
            delete frame;
            delete fd;
            return NULL;
        }
        frame->setFont(fd);
    }

    frame->setTexture(tex);
    
    m_allSpriteFrames[key] = frame;
    frame->setCacheKey(key);
    frame->retain();
    return frame;
}

GLTexture* GLCache::addTexture(const String& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
    }
    auto iter2 = m_allTextures.find(file.absolutePath());
    GLTexture* tex=NULL;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        ImageData image;
        if(image.loadFromFile(file.absolutePath()))
        {
            tex = new GLTexture();
            tex->initWithImage(&image);
        }
        else {
            EM(ERROR_IMAGE_LOAD_FAILD,path);
            return NULL;
        }
        m_allTextures[file.absolutePath()] = tex;
        tex->setCacheKey(file.absolutePath());
        tex->retain();
    }
    return tex;
}

SpriteFrame* GLCache::addFrame(const String& picKey,const String& plist)
{
    if (plist.empty()) {
        FileInfo file(picKey);
        if (!file.exist()) {
            EM(ERROR_FILE_NOT_EXIST,picKey);
        }
        auto iter = m_allSpriteFrames.find(file.absolutePath());
        if (iter != m_allSpriteFrames.end()) {
            return iter->second;
        }
        auto iter2 = m_allTextures.find(file.absolutePath());
        GLTexture* tex=NULL;
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
        EM("暂时不支持Plist格式");
        return NULL;
    }
}

SpriteFrame* GLCache::addFrame(const String& path,const Rect& rect)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
    }
    String key = String::fromFormat("%s_%d_%d_%d_%d",file.absolutePath().c_nstr(),(int)rect.x,(int)rect.y,(int)rect.width,(int)rect.height);
    auto iter = m_allSpriteFrames.find(key);
    if (iter != m_allSpriteFrames.end()) {
        return iter->second;
    }
    auto iter2 = m_allTextures.find(file.absolutePath());
    GLTexture* tex=NULL;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        tex = addTexture(file.absolutePath());
    }
    SpriteFrame* frame = new SpriteFrame();
    frame->setTexture(tex);
    frame->setRect(rect);
    m_allSpriteFrames[key] = frame;
    frame->setCacheKey(key);
    frame->retain();
    return frame;
}

GLTexture* GLCache::addTexture(int r)
{
    String pickKey = String::fromFormat("round%d",r);
    auto iter2 = m_allTextures.find(pickKey);
    GLTexture* tex=NULL;
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
    String pickKey = String::fromFormat("round%d",r);
    auto iter = m_allSpriteFrames.find(pickKey);
    if (iter != m_allSpriteFrames.end()) {
        return iter->second;
    }
    auto iter2 = m_allTextures.find(pickKey);
    GLTexture* tex=NULL;
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
