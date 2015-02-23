//
//  de-storage-file.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-storage-file.h"
#include "de-storage-interface.h"
#include "de.h"

NAMESPACE_DE_STORAGE

File::File()
:m_file(null)
{
    
}

File::~File()
{
    close();
}


bool File::open()
{
    updateFullPath();
    if (m_fullPath == "") {
        EM(E_STORAGE_FILE_NOT_FIND,m_fileName.c_str());
        return false;
    }
    if (!m_file) {
        m_file = fopen(m_fullPath.c_str(), "rb");
    }
    if (m_file) {
        fseek(m_file,0,SEEK_END);
        m_data.setSize(ftell(m_file));
        fseek(m_file,0,SEEK_SET);
        unsigned char* data = new unsigned char[m_data.getSize()+1];
        fread(data,sizeof(unsigned char), m_data.getSize(),m_file);
        data[m_data.getSize()] = '\0';
        m_data.setBytes(data);
        return true;
    }
    return false;
}

void File::close()
{
    if (m_file) {
        fclose(m_file);
        m_file = null;
    }
}


long File::getSize()
{
    return m_data.getSize();
}


bool File::exist()
{
    updateFullPath();
    if (m_fullPath == "")
    {
        return false;
    }
    return true;
}

void File::updateFullPath()
{
    string path;
    if (m_fullPath != "")
    {
        convert_wstring_to_string(m_fileName, path);
        if (m_fullPath.find(path.c_str()) != m_fullPath.npos) {
            return;
        }
    }
    de_string full = de::storage::searchers()->getFullPath(m_fileName);
    convert_wstring_to_string(full, path);
    m_fullPath = path;
}

NAMESPACE_DE_END2