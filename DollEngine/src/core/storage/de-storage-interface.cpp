//
//  de-storage-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-storage-interface.h"
#include "de.h"

NAMESPACE_DE_STORAGE

Searchers* searchers()
{
    return Searchers::GetInstance();
}

bool add_font(const de_string&path)
{
    return de::fonts::Fonts::GetInstance()->addFont(path);
}

de_string get_full_path(const de_string& path)
{
    return searchers()->getFullPath(path);
}


NAMESPACE_DE_END2
