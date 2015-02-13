//
//  TJSTouchEvent.h
//  Krkr_GL
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__TJSTouchEvent__
#define __Krkr_GL__TJSTouchEvent__

#include "GlobalTJS.h"
#include "Krkr_GL.h"
#include "TJSCOM.h"

iTJS_COM(TouchEvent)
virtual void onMouseDown(float x,float y );
virtual void onMouseUp(float x,float y );
virtual void onMouseMove(float x,float y );
virtual void onClick(float x,float y);
virtual void onMouseEnter();
virtual void onMouseLeave();
};

#endif /* defined(__Krkr_GL__TJSTouchEvent__) */
