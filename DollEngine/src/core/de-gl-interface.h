//
//  de-gl-interface.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_gl_interface__
#define __DollEngine__de_gl_interface__

#include "de-functions.h"

NAMESPACE_DE_GL

DE_EXTERN bool initialize();
DE_EXTERN void check_error();
DE_EXTERN void reset_viewport();

NAMESPACE_DE_END2


#endif /* defined(__DollEngine__de_gl_interface__) */
