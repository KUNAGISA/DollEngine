//
//  FontCache.h
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef DECore_FontCache_h
#define DECore_FontCache_h

#include "CoreUnits.h"
#include "ImageData.h"

struct FT_FaceRec_;
typedef struct FT_FaceRec_*  FT_Face;
struct FT_LibraryRec_;
typedef struct FT_LibraryRec_  *FT_Library;

DE_BEGIN

class FontCache
{
public:
    FontCache();
    ~FontCache();
    Shared(FontCache)
    
    ImageData* addText(const string& text,const string& fontName,int fontSize,FontData* fd);
    FT_Face getFont(const string& fontName);
    string addFont(const string& path);
    void removeFont(const string& fontName);
    
protected:
    map<string,FT_Face> m_allFonts;
    map<string,string> m_allFontPaths;//path : name
    FT_Library m_fontLibrary;
public:
    
    static string GetKeyByFont(const string& str,const string& fontName,int fontSize,int outlineSize);
};


DE_END

#endif
