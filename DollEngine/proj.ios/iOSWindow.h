//
//  iOSWindow.h
//  DollEngineIOS
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifndef __DollEngine__iOSWindow__
#define __DollEngine__iOSWindow__

DE_BEGIN

class iOSWindow : public Window
{
public:
	iOSWindow();
	virtual ~iOSWindow();

    void setVisible(bool visible);
    
protected:
	void* m_iosWindow;
};

DE_END


#endif /* defined(__DollEngine__iOSWindow__) */
