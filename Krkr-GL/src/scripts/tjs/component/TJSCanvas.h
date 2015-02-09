//
//  TJSCanvas.h
//  DollEngine
//
//  Created by DollStudio on 14/11/23.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TJSCanvas__
#define __DollEngine__TJSCanvas__

#include "Canvas.h"
#include "GlobalTJS.h"
#include "TJSCOM.h"

iTJS_COM(Canvas)
    bool loadImages(ttstr v){
        return Canvas::loadImages(v.AsStdString());
    }
    iTJS_GET_STR(Canvas, GraphPath)
};

#endif /* defined(__DollEngine__TJSCanvas__) */
