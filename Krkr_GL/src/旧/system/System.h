//
//  System.h
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__System__
#define __Krkr_GL__System__

#include "Functions.h"

class Window;
class System
{
public:
    Shared(System);
    System();
public:
    wstring addFont(const wstring& path);
    void removeFont(const wstring& name);
    FT_Face getFont(const wstring& fontName);
public:
	void addContinuousHandler();
	void assignMessage(int id, const wstring& msg);
	void createAppLock(const wstring& key);
	wstring createUUID();
	void doCompact();
	void exit();
	void getArgument();
	bool getKeyState(int code);
	int getTickCount();
	void inform(const wstring& text, const wstring& caption);
	wstring inputString(const wstring& caption,const wstring& prompt, const wstring& initialString);
	wstring readRegValue(const wstring& key);
	void removeContinuousHandler();
	void shellExecute(const wstring& target,const wstring& param);
	void terminate();
	int toActualColor(int color);
	void touchImages(const wstring& storages, int limitbytes, int timeout);
    
public:
    PROPERTY_RO(FT_Library, FontLibrary, m_fontLibrary);
    
    PROPERTY(float, DesktopHeight, m_desktopHeight){m_desktopHeight=v;}//桌面大小（即桌面或手机屏幕的分辨率)
    PROPERTY(float, DesktopLeft, m_desktopLeft){m_desktopLeft=v;}
    PROPERTY(float, DesktopTop, m_desktopTop){m_desktopTop=v;}
    PROPERTY(float, DesktopWidth, m_desktopWidth){m_desktopWidth=v;}
    PROPERTY(float, ScreenHeight, m_screenHeight);//逻辑宽高
    PROPERTY(float, ScreenWidth, m_screenWidth);
    
    PROPERTY(Window*, MainWindow, m_mainWindow){m_mainWindow=v;}
    PROPERTY(bool, EventDisabled, m_eventDisabled){m_eventDisabled=v;}//是否接收事件
    PROPERTY(float, GraphicCacheLimit, m_graphicCacheLimit){m_graphicCacheLimit=v;}//图像缓存限制
    PROPERTY_CONST(wstring, ExceptionHandler, m_exceptionHandler){m_exceptionHandler=v;}//异常捕捉事件函数
    PROPERTY_CONST(wstring, OnActivate, m_onActivate){m_onActivate=v;}//当系统到前台时触发的函数
    PROPERTY_CONST(wstring, OnDeactivate, m_onDeactivate){m_onDeactivate=v;}//当系统到后台时触发的函数

    PROPERTY_CONST(wstring, ExeName, m_exeName){m_exeName=v;}//exe或app名字
    PROPERTY_CONST(wstring, ExePath, m_exePath){m_exePath=v;}//app目录
    PROPERTY_CONST(wstring, AppDataPath, m_appDataPath){m_appDataPath=v;}//脚本目录
    PROPERTY_CONST(wstring, PersonalPath, m_personalPath){m_personalPath=v;}//主目录路径（ios中为docement目录
    PROPERTY_CONST(wstring, PatchPath, m_patchPath){m_patchPath=v;}//脚本补丁路径（ios中为cache目录

    PROPERTY_CONST(wstring, OsName, m_osName){m_osName=v;}//操作系统名称，和平台名称相比会具体到
    PROPERTY_CONST(wstring, PlatformName, m_platformName){m_platformName=v;}//平台名称，如iOS、Mac
    PROPERTY_CONST(wstring, Title, m_title){m_title=v;}//游戏标题
    PROPERTY_CONST(wstring, VersionInformation, m_versionInformation){m_versionInformation=v;}//版本信息，返回的是KrGL的版本信息以及著作权及协议内容
    PROPERTY_CONST(wstring, VersionString, m_versionString){m_versionString=v;}//版本号
    
    PROPERTY(bool, OrderChanged, m_orderChanged){m_orderChanged=v;}
    PROPERTY(bool, TransChanged, m_transChanged){m_transChanged=v;}
    
protected:
    map<wstring, FT_Face> m_fontFaceByName;
    map<wstring, wstring> m_fontNameByPath;
};

#endif /* defined(__Krkr_GL__System__) */
