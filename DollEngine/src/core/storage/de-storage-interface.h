//
//  de-storage-interface.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_storage_interface__
#define __DollEngine__de_storage_interface__

#include "de-functions.h"
#include "de-storage-searchs.h"

NAMESPACE_DE_STORAGE

DE_EXTERN de_string get_app_path();
DE_EXTERN de_string get_data_path();
DE_EXTERN de_string get_cache_path();

DE_EXTERN storage_searchs* searchs();
DE_EXTERN void initialize();

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_interface__) */
