//
//  FileInfo.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__FileInfo__
#define __DollEngine__FileInfo__

#include "Units.h"
#include "IOData.h"

DE_BEGIN

class FileInfo
{
    enum FILE_EXIST_STATUS
    {
        FILE_UNKNOW=0,
        FILE_EXIST=1,
        FILE_NOTEXIST=2,
    };
public:
    FileInfo();
    FileInfo(const string& path);
    
public:
    
    void setPath(const string& path);
    
    string fileExt();
    string fileNameIgnoreExt();
    string fileName();
    string absolutePath();
    bool exist(bool cache=true);
    bool isDir();
    
protected:
    FILE_EXIST_STATUS m_status;
    string m_path;
    string m_fileExt;
    string m_absolutePath;
    string m_fileName;
    string m_fileNameIgnoreExt;
};

DE_END

#endif /* defined(__DollEngine__FileInfo__) */
