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
#include "PaintProgram.h"
#include "FileInfo.h"
#include "System.h"

DE_BEGIN

GLCache::GLCache()
{
}

TextFrame* GLCache::addText(const String& text,const String& fontName,int fontSize)
{
//    String _fontName;
//    if (fontName.empty() || text.empty()) {
//        _fontName = DEFFONT;
//    }
//    else {
//        _fontName = fontName;
//    }
    
//    if (fontSize == 0 || text.empty()) {
//        fontSize = DEFFONTSIZE;
//    }
    
//    String key = System::GetKeyByFont(text,fontName,fontSize,0);
    
//    auto iter = m_allImageInfos.find(key);
//    if (iter != m_allImageInfos.end()) {
//        return dynamic_cast<TextFrame*>(iter->second);
//    }
    
    TextFrame* frame = new TextFrame();
//    Texture* tex= NULL;
//    auto iter2 = m_allTextures.find(key);
//    if(iter2 != m_allTextures.end()) {
//        tex = iter2->second;
//    }
//    else {
        
//        FontData* fd = new FontData();
        
//        PictureData* image = System::GetInstance()->addText(text, fontName, fontSize,fd);
        
//        tex = new Texture();
//        if(tex->initWithImage(image)) {
//            delete image;
//        }
//        else {
//            delete image;
//            delete tex;
//            delete frame;
//            delete fd;
//            return NULL;
//        }
//        frame->setFont(fd);
//    }

//    frame->setTexture(tex);
    
//    m_allImageInfos[key] = frame;
    return frame;
}

Texture* GLCache::addTexture(const String& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
    }
    auto iter2 = m_allTextures.find(file.absolutePath());
    Texture* tex=NULL;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        PictureData image;
        if(image.loadFromFile(file.absolutePath()))
        {
            tex = new Texture();
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

ImageInfo* GLCache::addFrame(const String& picKey,const String& plist)
{
    if (plist.empty()) {
//        FileInfo file(picKey);
//        if (!file.exist()) {
//            EM(ERROR_FILE_NOT_EXIST,picKey);
//        }
//        auto iter = m_allImageInfos.find(file.absolutePath());
//        if (iter != m_allImageInfos.end()) {
//            return iter->second;
//        }
//        auto iter2 = m_allTextures.find(file.absolutePath());
//        Texture* tex=NULL;
//        if(iter2 != m_allTextures.end()) {
//            tex = iter2->second;
//        }
//        else {
//            tex = addTexture(picKey);
//        }
        ImageInfo* frame = new ImageInfo();
//        frame->setTexture(tex);
        
//        m_allImageInfos[file.absolutePath()] = frame;
        return frame;
    }
    else {
        EM("暂时不支持Plist格式");
        return NULL;
    }
}

ImageInfo* GLCache::addFrame(const String& path,const Rect& rect)
{
//    FileInfo file(path);
//    if (!file.exist()) {
//        EM(ERROR_FILE_NOT_EXIST,path);
//    }
//    String key = String::fromFormat("%s_%d_%d_%d_%d",file.absolutePath().c_nstr(),(int)rect.x,(int)rect.y,(int)rect.width,(int)rect.height);
//    auto iter = m_allImageInfos.find(key);
//    if (iter != m_allImageInfos.end()) {
//        return iter->second;
//    }
//    auto iter2 = m_allTextures.find(file.absolutePath());
//    Texture* tex=NULL;
//    if(iter2 != m_allTextures.end()) {
//        tex = iter2->second;
//    }
//    else {
//        tex = addTexture(file.absolutePath());
//    }
    ImageInfo* frame = new ImageInfo();
//    frame->setTexture(tex);
//    frame->setOrginRect(rect);
//    m_allImageInfos[key] = frame;
    return frame;
}

Texture* GLCache::addTexture(int r)
{
    String pickKey = String::fromFormat("round%d",r);
    auto iter2 = m_allTextures.find(pickKey);
    Texture* tex=NULL;
//    if(iter2 != m_allTextures.end()) {
//        tex = iter2->second;
//    }
//    else {
//        tex = new Texture();
//        PictureData* image = PictureData::createRoundRect(r);
//        tex->initWithImage(image);
//        delete image;
//        m_allTextures[pickKey] = tex;
//        tex->setCacheKey(pickKey);
//        tex->retain();
//    }
    return tex;
}//创建圆角矩形

ImageInfo* GLCache::addFrame(int r)
{
//    String pickKey = String::fromFormat("round%d",r);
//    auto iter = m_allImageInfos.find(pickKey);
//    if (iter != m_allImageInfos.end()) {
//        return iter->second;
//    }
//    auto iter2 = m_allTextures.find(pickKey);
    Texture* tex=NULL;
//    if(iter2 != m_allTextures.end()) {
//        tex = iter2->second;
//    }
//    else {
//        tex = addTexture(r);
//    }
    ImageInfo* frame = new ImageInfo();
    frame->setTexture(tex);
    
    return frame;
    
}//创建圆角矩形

void GLCache::removeImageInfoCache(ImageInfo* frame)
{
}

void GLCache::removeTextureCache(Texture* frame)
{
    m_allTextures.erase(frame->getCacheKey());
}

DE_END
