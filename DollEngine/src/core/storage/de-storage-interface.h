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

NAMESPACE_DE_STORAGE
class Searchers;

DE_EXTERN de_string get_exe_path();
DE_EXTERN de_string get_app_path();
DE_EXTERN de_string get_data_path();
DE_EXTERN de_string get_cache_path();
DE_EXTERN de_string get_full_path(const de_string& path);
DE_EXTERN bool add_font(const de_string&path);
DE_EXTERN Searchers* searchers();

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_interface__) */
