//
//  de-gl-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-gl-interface.h"

NAMESPACE_DE_GL

bool initialize()
{
#ifdef OS_IOS
    glGenFramebuffers(1, &m_frame_buffer);
    if(!m_frame_buffer) {THROW_EM(ERROR_PaintEngine_INIT_FAILD_FRAME);}
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);
    
    glGenRenderbuffers(1, &m_colorRenderbuffer);
    if(!m_colorRenderbuffer) {THROW_EM(ERROR_PaintEngine_INIT_FAILD_RENDER);}
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8,
                          System::GetInstance()->getScreenWidth(),
                          System::GetInstance()->getScreenHeight());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer);
    
    CHECK_GL_ERROR;
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
    if(status != GL_FRAMEBUFFER_COMPLETE) {
        DM("failed to make complete framebuffer object %x", status);
    }
#endif
    
#ifdef OS_MAC
    glEnable(GL_TEXTURE_2D);
    CHECK_GL_ERROR;
#endif
    glDisable(GL_DEPTH_TEST);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    return true;
}

static GLint s_gl_error_enum =0;
void check_error()
{
    s_gl_error_enum = glGetError();
    if(s_gl_error_enum!=0){}
//        EM(ERROR_OPENGL_UNKNOW,s_gl_error_enum);
}

NAMESPACE_DE_END


