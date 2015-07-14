//
//  FileInfo.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "FileInfo.h"
#include "Storages.h"

DE_BEGIN

FileInfo::FileInfo()
:m_status(FILE_UNKNOW)
{
    
}

FileInfo::FileInfo(const string& path)
{
    setPath(path);
}

void FileInfo::setPath(const string &path)
{
    if (m_path != path) {
        m_status = FILE_UNKNOW;
        m_fileNameIgnoreExt = "";
        m_fileName = "";
        m_absolutePath = "";
        m_fileExt = "";
        m_path = path;
    }
}

string FileInfo::fileExt()
{
    if (m_fileExt == "") {
        fileName();
        string::size_type t = m_fileName.rfind(".");
        if (t != string::npos) {
            m_fileNameIgnoreExt = m_fileName.substr(m_fileName.rfind(".")+1);
        }
        else {
            m_fileNameIgnoreExt = "";
        }
    }
    return m_fileExt;
}

string FileInfo::fileNameIgnoreExt()
{
    if (m_fileNameIgnoreExt == "") {
        fileName();
        string::size_type t = m_fileName.rfind(".");
        if (t != string::npos) {
            m_fileNameIgnoreExt = m_fileName.substr(m_fileName.rfind(".")+1);
        }
        else {
            m_fileNameIgnoreExt = "";
        }
        
    }
    return m_fileNameIgnoreExt;
}

string FileInfo::fileName()
{
    if (m_fileName=="") {
        string::size_type t = m_path.rfind("/");
        if (t != string::npos) {
            m_fileName = m_path.substr(m_path.rfind("/")+1);
        }
        else {
            m_fileName = m_path;
        }
    }
    return m_fileName;
}

string FileInfo::absolutePath()
{
    if (exist()) {
        return m_absolutePath;
    }
    else {
        return m_path;
    }
}


bool FileInfo::exist(bool cache)
{
    if (m_status == FILE_UNKNOW || cache == false) {
        m_absolutePath = Storages::GetInstance()->getFullPath(m_path);
        if (m_absolutePath != "") {
            m_status = FILE_EXIST;
        }
        else {
            m_status = FILE_NOTEXIST;
        }
    }
    return m_status==FILE_EXIST;
}

bool FileInfo::isDir()
{
    return false;
}


DE_END