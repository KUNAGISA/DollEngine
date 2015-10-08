#include "DrawInterface.h"

DE_BEGIN

static DrawInterface* _instance=NULL;

DrawInterface::DrawInterface()
{
    
}

DrawInterface* DrawInterface::GetInstance()
{
    if(!_instance) {
        _instance = new DrawInterface();
#ifdef __QT__
        _instance->initializeOpenGLFunctions();
#endif
    }
    return _instance;
}

void DrawInterface::deleteFBO(DrawSizeI n, const DrawFBOId * framebuffers)
{
    glDeleteFramebuffers(n,(GLuint*)framebuffers);
}

DrawFBOId DrawInterface::createFBO(DrawTexId texId )
{
    DrawFBOId newFBO;
    DrawFBOId oldFBO;
    GLint oldRBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)(&oldFBO));
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
    
    glGenFramebuffers(1, &newFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, newFBO);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
    ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
    return newFBO;
}

void DrawInterface::switchFBO(DrawFBOId* oldFBO,DrawFBOId newFBO)
{
    if(oldFBO){
        glGetIntegerv(GL_FRAMEBUFFER_BINDING,  (GLint*)oldFBO);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, newFBO);
}

void DrawInterface::clearColor(DrawMask mask,DrawClampF red,DrawClampF green,DrawClampF blue,DrawClampF alpha)
{
    if(mask!=0)
    {
        glClear(mask);
    }
    glClearColor(red,green,blue,alpha);
}

DrawTexId DrawInterface::loadTexture(void* data, int width,int height)
{
    DrawTexId m_textureId;
    glGenTextures(1,&m_textureId);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width,height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data );
    CHECK_GL_ERROR;
    return m_textureId;
}

void DrawInterface::bindTexture(DrawActiveTexId aid,DrawTexId bid)
{
    glActiveTexture(aid);
    glBindTexture(GL_TEXTURE_2D, bid);
    CHECK_GL_ERROR;
}

void DrawInterface::deleteTexture(DrawSizeI count,DrawTexId* texId)
{
    glDeleteTextures(count,texId);
}

DE_END
