//
//  GLCache.h
//  DollEngine
//
//  Created by DollStudio on 15/5/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLCache__
#define __DollEngine__GLCache__

#include "Units.h"

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
    GLTexture* addTexture(const string& picKey);
    SpriteFrame* addFrame(const string& picKey,const string& plist="");
    void removeSpriteFrameCache(SpriteFrame* frame);
    void removeTextureCache(GLTexture* frame);
    
public:
    PROPERTY_RO(FT_Library, FontLibrary, m_fontLibrary);
    FT_Face getFont(const string& fontName);
    string addFont(const string& path);
    void removeFont(const string& fontName);
protected:
    map<string,string > m_allPlist;
    map<string,SpriteFrame*> m_allSpriteFrames;
    map<string,GLTexture*> m_allTextures;
    map<string,FT_Face> m_allFonts;
    map<string,string> m_allFontPaths;//path : name
public:
    
    static string GetKeyByFont(const string& str,const string& fontName,int fontSize,int outlineSize);
    
};

DE_END


#endif /* defined(__DollEngine__GLCache__) */
