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

static storage_searchs* s_searchs_instance=null;

storage_searchs* searchs()
{
    if (!s_searchs_instance) {
        s_searchs_instance = new storage_searchs();
    }
    return s_searchs_instance;
}

void initialize()
{
    searchs()->setResourcePath(get_app_path());
    searchs()->setDocumentPath(get_data_path());
    searchs()->setCachePath(get_cache_path());
}

NAMESPACE_DE_END2
