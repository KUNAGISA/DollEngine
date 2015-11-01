//
//  TjsWindow.h
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsWindow__
#define __DollEngine__TjsWindow__

#include "TjsBind.h"
#include "QtWindow.h"

TJS_NCB(QtWindow){}
void setTitle(tTJSVariant v){
    TJS_STRING(v, str);
    QtWindow::setTitle(str);
}
tTJSVariant getTitle(){
    return m_title.c_str();
}

};

#endif /* defined(__DollEngine__TjsWindow__) */
