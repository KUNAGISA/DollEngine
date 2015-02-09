//
//  System.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "System.h"
#include "Storages.h"
#include "PaintEngine.h"
#include "Window.h"
#include "Scripts.h"
#include "AsyncTrigger.h"
#include "StringUtils.h"

System::System()
:m_desktopLeft(0)
,m_desktopTop(0)
,m_desktopWidth(1)
,m_desktopHeight(1)
,m_screenWidth(1)
,m_screenHeight(1)
,m_mainWindow(null)
,m_transChanged(false)
,m_orderChanged(false)
{
    m_exePath = get_app_path();
    DM("appPath:%ls;\n",m_exePath.c_str());
    m_appDataPath = m_exePath + L"data/";
    DM("appDataPath:%ls;\n",m_appDataPath.c_str());
    m_personalPath = get_document_path();
    DM("personalPath:%ls;\n",m_personalPath.c_str());
    m_patchPath = get_cache_path();
    DM("patchPath:%ls;\n",m_patchPath.c_str());
    
    FT_Error ft_err = FT_Init_FreeType(&m_fontLibrary);
    CHECK_FT_ERROR
}

void System::setScreenWidth( float v)
{
    m_screenWidth=v;
}

void System::setScreenHeight( float v)
{
    m_screenHeight=v;
}

wstring System::addFont(const wstring& path)
{
    wstring fullPath = Storages::GetInstance()->getFullPath(path);
    if (fullPath.size() == 0) {
        EM(ERROR_FILE_OPENFAIL_PATH_CANTFIND,path.c_str());
        return L"";
    }
    auto iter = m_fontNameByPath.find(fullPath);
    if (iter == m_fontNameByPath.end())
    {
        string sfullPath;
        StringUtils::ConvertUnicodeToUtf8(fullPath, sfullPath);
        FT_Face face;
        FT_Error ft_err = FT_New_Face(m_fontLibrary, sfullPath.c_str(), 0, &face);
        if (ft_err) {
            return L"";
        }
        ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (ft_err) {
            FT_Done_Face(face);
            return L"";
        }
        wstring familyName;
        StringUtils::ConvertUtf8ToUnicode(face->family_name, familyName);
        m_fontNameByPath[fullPath] = familyName;
        auto iter2 = m_fontFaceByName.find(familyName);
        if (iter2 == m_fontFaceByName.end())
        {
            m_fontFaceByName[familyName] = face;
            DM("User add font:%s",face->family_name);
            return familyName;
        }
        FT_Done_Face(face);
        return iter2->first;
    }
    return iter->second;
}

void System::removeFont(const wstring& name)
{
    auto iter = m_fontFaceByName.find(name);
    if (iter != m_fontFaceByName.end()) {
        for (auto iter2 = m_fontNameByPath.begin();
             iter2 != m_fontNameByPath.end();++iter2)
        {
            if (iter2->second == name)
            {
                m_fontNameByPath.erase(iter2);
                break;
            }
        }
        FT_Done_Face(iter->second);
        m_fontFaceByName.erase(iter);
    }
}

FT_Face System::getFont(const wstring& fontName)
{
    auto iter = m_fontFaceByName.find(fontName);
    if (iter != m_fontFaceByName.end())
    {
        return iter->second;
    }
    return null;
}