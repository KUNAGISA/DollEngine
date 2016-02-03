//
//  System.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__System__
#define __DollEngine__System__

#include "CoreTypes.h"
#include "SystemDelegate.h"

DE_BEGIN

class PictureData;

class System
{
public:
    System();
    Shared(System)
    virtual ~System();
    
public:
    void startup(); //脚本入口
    void stopMainLoop();
    void startMainLoop();
    void doCompact();
    
    String addFont(const String& filePath);
    void* getFont(const String& fontName);

    void removeFont(const String& fontName);
    
    static String GetKeyByFont(const String& str,const String& fontName,int fontSize,int outlineSize) {
        return str+L"_"+fontName+L"_"+String(fontSize)+L"_"+String(outlineSize);
    }

    void openUrl(const String& url);
    
    int64_t getMilliSeconds();
    double getSeconds();
    
    PROPERTY(SystemDelegate*,Delegate,m_delegate){m_delegate=v;}
    
    PROPERTY(bool,IsError,m_isError){m_isError=v;}
    
    //debug mode:0不显示console 1显示但不打印tag 2打印tag但不打印macro 3所有都打印
    PROPERTY(int,DebugMode,m_debugMode);
    
    PROPERTY_CONST(String,PlatformName,m_platformName){m_platformName=v;}
    PROPERTY_CONST(String,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(String,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(String,GamePath,m_gamePath){m_gamePath=v;}
    PROPERTY_CONST(String,SaveDataPath,m_saveDataPath){m_saveDataPath=v;}
    PROPERTY_CONST(String,PatchPath,m_patchPath){m_patchPath=v;}
    
    float getDesktopWidth();
    float getDesktopHeight();
    
    const String& getDefFontName(){return m_defFontName;}
    static bool NeedRedraw;
    static bool NeedSortTouches;
    
protected:
    map<String, void*> m_allFonts;
    map<String, String> m_allFontPaths;
    String m_defFontName;
};

DE_END

#endif /* defined(__DollEngine__Device__) */
