//
//  iOSWindow.h
//  DollEngineIOS
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//


#ifndef __DollEngine__iOSWindow__
#define __DollEngine__iOSWindow__

#include "Window.h"

DE_BEGIN

class iOSWindow : public Window
{
public:
	iOSWindow();
	virtual ~iOSWindow();

    void setVisible(bool visible);
    void setSize(int w,int h);
protected:
    void* m_iosWindow;
    void* m_iosViewCtl;
};

DE_END


#endif /* defined(__DollEngine__iOSWindow__) */
