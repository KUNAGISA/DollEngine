//
//  GLFunctions.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GLFunctions__
#define __DollEngine__GLFunctions__

#include "Units.h"

DE_BEGIN
namespace GL {
    extern void setProjectionMatrixDirty();
    extern void blendFunc(GLenum src, GLenum dst);
    extern void bindVAO(GLuint vaoId);
    extern void checkError();
}

DE_END

#endif /* defined(__DollEngine__GLFunctions__) */
