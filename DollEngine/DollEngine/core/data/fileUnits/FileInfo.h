//
//  FileInfo.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__FileInfo__
#define __DollEngine__FileInfo__

#include "CoreUnits.h"
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
    FileInfo(const String& path);
    
public:
    
    void setPath(const String& path);
    
    String fileExt();
    String fileNameIgnoreExt();
    String fileName();
    String absolutePath();
    bool exist(bool cache=true);
    bool isDir();
    
protected:
    FILE_EXIST_STATUS m_status;
    String m_path;
    String m_fileExt;
    String m_absolutePath;
    String m_fileName;
    String m_fileNameIgnoreExt;
};

DE_END

#endif /* defined(__DollEngine__FileInfo__) */
