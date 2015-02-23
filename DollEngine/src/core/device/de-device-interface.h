//
//  de-device-interface.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_device_interface__
#define __DollEngine__de_device_interface__

#include "de-functions.h"
#include "de-device-window.h"
#include "de-Transform.h"

NAMESPACE_DE_DEVICE

DE_EXTERN Window* window(Window* v=null);
DE_EXTERN Transform* main_trans();
DE_EXTERN void init_window();
DE_EXTERN void reset_viewport();
DE_EXTERN float get_window_edge_width();
DE_EXTERN float get_window_edge_height();
DE_EXTERN float get_inner_width();
DE_EXTERN float get_inner_height();


NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_device_interface__) */
