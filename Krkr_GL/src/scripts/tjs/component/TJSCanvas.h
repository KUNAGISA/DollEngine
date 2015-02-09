//
//  TJSCanvas.h
//  Krkr_GL
//
//  Created by DollStudio on 14/11/23.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__TJSCanvas__
#define __Krkr_GL__TJSCanvas__

#include "Canvas.h"
#include "GlobalTJS.h"
#include "TJSCOM.h"

iTJS_COM(Canvas)
    bool loadImages(ttstr v){
        return Canvas::loadImages(v.AsStdString());
    }
    iTJS_GET_STR(Canvas, GraphPath)
};

#endif /* defined(__Krkr_GL__TJSCanvas__) */
