//
//  de-painter-interface.h
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_painter_interface__
#define __DollEngine__de_painter_interface__

#include "de-functions.h"

NAMESPACE_DE_PAINTER
class Image;

DE_EXTERN void reset_viewport();
DE_EXTERN Image* get_image(const de_string& path);

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_painter_interface__) */
