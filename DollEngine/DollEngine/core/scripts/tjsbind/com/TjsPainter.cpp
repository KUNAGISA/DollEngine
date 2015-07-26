//
//  TjsPainter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsPainter.h"

NCB_REGISTER_CLASS_DIFFER(Painter, TjsPainter)
{
    TJS_FACTORY_COM
    NCB_METHOD(loadImages);
    NCB_METHOD(loadSize);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
};
