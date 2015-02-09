//
//  TJSTouchEvent.h
//  DollEngine
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TJSTouchEvent__
#define __DollEngine__TJSTouchEvent__

#include "GlobalTJS.h"
#include "Krkr-GL.h"
#include "TJSCOM.h"

iTJS_COM(TouchEvent)
virtual void onMouseDown(float x,float y );
virtual void onMouseUp(float x,float y );
virtual void onMouseMove(float x,float y );
virtual void onClick(float x,float y);
virtual void onMouseEnter();
virtual void onMouseLeave();
};

#endif /* defined(__DollEngine__TJSTouchEvent__) */
