//
//  de-scripts-tjs.h
//  DollEngine
//
//  Created by DollStudio on 15/2/14.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_scripts_tjs__
#define __DollEngine__de_scripts_tjs__

#include "de-functions.h"

namespace TJS {
    class tTJSVariant;
};
NAMESPACE_DE_SCRIPT

DE_EXTERN void initialize();
DE_EXTERN void exec_storage(const de_string& filename,de_var* ret);
DE_EXTERN void eval_storage(const de_string& filename,de_var* ret);
DE_EXTERN void exec(const de_char* code,de_var* ret);
DE_EXTERN void eval(const de_char* code,de_var* ret);
DE_EXTERN void push_script_file(const de_string& filename);
DE_EXTERN void pop_script_file();
DE_EXTERN de_string get_cur_file();
DE_EXTERN void* script_global();

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_scripts_tjs__) */
