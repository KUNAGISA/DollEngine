//
//  System.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "System.h"
#include "PictureData.h"
#include "FileInfo.h"
#include <ft2build.h>
#include FT_FREETYPE_H


DE_BEGIN

static FT_Library g_fontLibrary=NULL;

System::System()
:m_debugMode(0)
,m_isError(false)
,m_delegate(NULL)
{
    m_platformName = L"iOS";
	
    System::NeedRedraw = true;
    System::NeedSortTouches = true;
    //Data path
    m_dataPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_dataPath += L"/data/";
    
    //App path
    m_appPath = [[NSBundle mainBundle] bundlePath].UTF8String;
    m_appPath += L"/";
    
    //SaveData path
    m_saveDataPath = [NSHomeDirectory()stringByAppendingPathComponent:@"Documents"].UTF8String;
    m_saveDataPath += L"/";
    
    //Patch path
    m_patchPath = m_saveDataPath;

    FT_Init_FreeType(&g_fontLibrary);
}

System::~System()
{
    FT_Done_FreeType(g_fontLibrary);
}

float System::getDesktopWidth()
{
    float w = [[UIScreen mainScreen] bounds].size.width*[UIScreen mainScreen].scale;
    return w;
}

float System::getDesktopHeight()
{
    float h = [[UIScreen mainScreen] bounds].size.height*[UIScreen mainScreen].scale;
    return h;
}


String System::addFont(const String& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
    }
    auto iter = m_allFontPaths.find(file.absolutePath());
    if (iter == m_allFontPaths.end())
    {
        FT_Face face;
        FT_Error ft_err = FT_New_Face(g_fontLibrary, file.absolutePath().c_nstr(), 0, &face);
        if (ft_err) {
            EM(ERROR_ADDFONT_FAILD);
        }
        ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (ft_err) {
            FT_Done_Face(face);
            EM(ERROR_ADDFONT_FAILD);
        }
        m_allFontPaths[file.absolutePath()] = face->family_name;
        auto iter2 = m_allFonts.find(face->family_name);
        if (iter2 == m_allFonts.end())
        {
            m_allFonts[face->family_name] = face;
            if (m_defFontName.empty()) {
                m_defFontName = face->family_name;
                DM("新增自定义字体:%s(默认字体)",face->family_name);
            }
            else {
                DM("新增自定义字体:%s",face->family_name);
            }
            return face->family_name;
        }
        FT_Done_Face(face);
        return iter2->first;
    }
    return iter->second;
}

void System::removeFont(const String& fontName)
{
    auto iter = m_allFonts.find(fontName);
    if (iter != m_allFonts.end()) {
        for (auto pair : m_allFontPaths) {
            if (pair.second == fontName) {
                m_allFontPaths.erase(pair.first);
                break;
            }
        }
        
        FT_Done_Face((FT_Face)iter->second);
        m_allFonts.erase(fontName);
    }
}

DE_END
