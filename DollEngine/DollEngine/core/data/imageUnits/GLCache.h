//
//  GLCache.h
//  DollEngine
//
//  Created by DollStudio on 15/5/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLCache__
#define __DollEngine__GLCache__

#include "CoreUnits.h"

DE_BEGIN

class SpriteFrame;
class GLTexture;
class TextFrame;

class GLCache
{
public:
    GLCache();
    Shared(GLCache)
    
    TextFrame* addText(const string& text,const string& fontName,int fontSize);
    GLTexture* addTexture(const string& path);
    SpriteFrame* addFrame(const string& picKey,const string& plist="");
    SpriteFrame* addFrame(const string& path,const Rect& rect);
    GLTexture* addTexture(int r);//创建圆角矩形
    SpriteFrame* addFrame(int r);//创建圆角矩形
    void removeSpriteFrameCache(SpriteFrame* frame);
    void removeTextureCache(GLTexture* frame);
    
protected:
    map<String,String > m_allPlist;
    map<String,SpriteFrame*> m_allSpriteFrames;
    map<String,GLTexture*> m_allTextures;
    
};

DE_END


#endif /* defined(__DollEngine__GLCache__) */
