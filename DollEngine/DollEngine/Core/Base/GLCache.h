//
//  GLCache.h
//  DollEngine
//
//  Created by DollStudio on 15/5/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLCache__
#define __DollEngine__GLCache__

#include "CoreTypes.h"

DE_BEGIN

class ImageInfo;
class Texture;
class TextFrame;

class GLCache
{
public:
    GLCache();
    Shared(GLCache)
    
    TextFrame* addText(const String& text,const String& fontName,int fontSize);
    Texture* addTexture(const String& path);
    ImageInfo* addFrame(const String& picKey,const String& plist="");
    ImageInfo* addFrame(const String& path,const Rect& rect);
    Texture* addTexture(int r);//创建圆角矩形
    ImageInfo* addFrame(int r);//创建圆角矩形
    void removeImageInfoCache(ImageInfo* frame);
    void removeTextureCache(Texture* frame);
    
protected:
    map<String,String > m_allPlist;
    map<String,Texture*> m_allTextures;
    
};

DE_END


#endif /* defined(__DollEngine__GLCache__) */
