//
//  de-storage-fonts.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/21.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-storage-fonts.h"
#include "de.h"
#include "fdv_res.h"

NAMESPACE_DE_FONTS

Fonts::Fonts()
{
    FT_Init_FreeType(&m_fontLibrary);
}

bool Fonts::addFont(const de_string& path)
{
    de_string fullPath = de::storage::get_full_path(path);
    if (fullPath.size() == 0) {
        EM(E_STORAGE_FILE_NOT_OPEN,path.c_str());
        return false;
    }
    auto iter = m_fontNameByPath.find(fullPath);
    if (iter == m_fontNameByPath.end())
    {
        string sfullPath;
        de::convert_wstring_to_string(fullPath, sfullPath);
        FT_Face face;
        FT_Error ft_err = FT_New_Face(m_fontLibrary, sfullPath.c_str(), 0, &face);
        if (ft_err) {
            return false;
        }
        ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (ft_err) {
            FT_Done_Face(face);
            return false;
        }
        wstring familyName;
        de::convert_utf8_to_wstring(face->family_name, familyName);
        m_fontNameByPath[fullPath] = familyName;
        auto iter2 = m_fontFaceByName.find(familyName);
        if (iter2 == m_fontFaceByName.end())
        {
            m_fontFaceByName[familyName] = face;
            DM("新增自定义字体:%s",face->family_name);
            return true;
        }
        FT_Done_Face(face);
        return true;
    }
    return false;
}

void Fonts::initDefautFont()
{
    FT_Face face;
    long length;
    const unsigned char* data = fdv::read_file("WenQuanYiMicroHei.ttc", length);
    FT_Error ft_err = FT_New_Memory_Face(m_fontLibrary, data, length, 0, &face);
    if (ft_err) {
        return;
    }
    ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
    if (ft_err) {
        FT_Done_Face(face);
        return;
    }
    
    wstring familyName;
    de::convert_utf8_to_wstring(face->family_name, familyName);
    m_fontNameByPath[DEFFONT] = DEFFONT;
    m_fontFaceByName[DEFFONT] = face;
    DM("新增自定义字体:%s",face->family_name);
}

NAMESPACE_DE_END2
