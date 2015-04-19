//
//  Storages.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Storages__
#define __DollEngine__Storages__

#include "Units.h"
#include "IOData.h"

DE_BEGIN

class Storages
{
public:
    Storages();
    Shared(Storages)
    static IOData* GetFileData(const string& fullpath);
    static IOData* GetFileString(const string& fullpath);
public:
    void addAutoPath(const string& storage);// ( 增加自动检索路径 )
    string getFullPath(const string& storage);// ( 获取统一文件路径 )
    void removeAutoPath(const string& storage);// ( 删除自动检索路径 )
private:
    list<string> m_autoPaths;
    map<string, string> m_searchPathsCache;
};

DE_END

#endif /* defined(__DollEngine__Storages__) */
