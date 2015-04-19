//
//  GLFunctions.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLFunctions.h"

DE_BEGIN

namespace GL {
    static GLint s_currentProjectionMatrix=-1;
    void setProjectionMatrixDirty()
    {
        s_currentProjectionMatrix = -1;
    }
    
    static void SetBlending(GLenum sfactor, GLenum dfactor)
    {
        if (sfactor == GL_ONE && dfactor == GL_ZERO)
        {
            glDisable(GL_BLEND);
        }
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(sfactor, dfactor);
        }
    }
    
    static GLenum s_blendingSource = -1;
    static GLenum s_blendingDest = -1;
    void blendFunc(GLenum sfactor, GLenum dfactor)
    {
        if (sfactor != s_blendingSource || dfactor != s_blendingDest)
        {
            s_blendingSource = sfactor;
            s_blendingDest = dfactor;
            SetBlending(sfactor, dfactor);
        }
    }
    
    static GLuint s_VAO=-1;
    void bindVAO(GLuint vaoId)
    {
        if (s_VAO != vaoId)
        {
            s_VAO = vaoId;
            glBindVertexArrayAPPLE(vaoId);
        }
    }

}

DE_END