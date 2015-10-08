//
//  TjsTimer.h
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsTimer__
#define __DollEngine__TjsTimer__

#include "TjsCOM.h"
#include "Timer.h"

TJS_NCB_COM(Timer)

void onTimer(){
    TJS_EVENT_CALL(onTimer, 0);
}
};

#endif /* defined(__DollEngine__TjsTimer__) */
