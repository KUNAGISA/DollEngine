#include "GLCanvas.h"
#include "CoreUnits.h"
#include "GLProgram.h"

DE_BEGIN


GLCanvas* GLCanvas::GetInstance()
{
    static GLCanvas* _instance=NULL;
    if(!_instance) {
        _instance = new GLCanvas();
#ifdef __QT__
        _instance->initializeOpenGLFunctions();
#endif
    }
    return _instance;
}

void GLCanvas::initialize()
{
    glEnable(GL_TEXTURE_2D);
    
    glDisable(GL_DEPTH_TEST);
    
    clearColor(GL_COLOR_BUFFER_BIT,0,0,0,0);
    
    CHECK_GL_ERROR;
    
}

static DrawBlendId s_blendingSource = -1;
static DrawBlendId s_blendingDest = -1;
void GLCanvas::blendFunc(DrawBlendId src,DrawBlendId dst)
{
    if (src != s_blendingSource || dst != s_blendingDest)
    {
        s_blendingSource = src;
        s_blendingDest = dst;
        if (src == GL_ONE && dst == GL_ZERO)
        {
            glDisable(GL_BLEND);
        }
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(src, dst);
        }
    }
}

void GLCanvas::deleteFBO(DrawSizeI n, const DrawFBOId * framebuffers)
{
    glDeleteFramebuffers(n,framebuffers);
}

DrawFBOId GLCanvas::createFBO(DrawTexId texId )
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

void GLCanvas::switchFBO(DrawFBOId* oldFBO,DrawFBOId newFBO)
{
    if(oldFBO){
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)oldFBO);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, newFBO);
    CHECK_GL_ERROR;
}

void GLCanvas::clearColor(DrawMask mask,DrawClampF red,DrawClampF green,DrawClampF blue,DrawClampF alpha)
{
    if(mask!=0)
    {
        glClear(mask);
    }
    glClearColor(red,green,blue,alpha);
}

DrawTexId GLCanvas::loadTexture(void* data, int width,int height)
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

void GLCanvas::bindTexture(DrawActiveTexId aid,DrawTexId bid)
{
    glActiveTexture(aid);
    glBindTexture(GL_TEXTURE_2D, bid);
    CHECK_GL_ERROR;
}

void GLCanvas::deleteTexture(DrawSizeI count,DrawTexId* texId)
{
    glDeleteTextures(count,texId);
}

void GLCanvas::readPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid *pixels)
{
    glReadPixels(x,y,width,height,format,type,pixels);
    CHECK_GL_ERROR;
}

DrawPrgId GLCanvas::createProgram()
{
    return glCreateProgram();
}

bool GLCanvas::linkProgram(DrawPrgId pId)
{
    glLinkProgram(pId);
    CHECK_GL_ERROR;
    
    GLint status;
    glGetProgramiv(pId, GL_LINK_STATUS, &status);
    CHECK_GL_ERROR;
    if (status == 0) {
        return false;
    }
    return true;
}

static GLuint s_currentProgramId=0;
void GLCanvas::useProgram(DrawPrgId pId)
{
    if (s_currentProgramId != pId) {
        s_currentProgramId = pId;
        glUseProgram(pId);
        CHECK_GL_ERROR;
    }
}

void GLCanvas::deleteProgram(DrawPrgId pId)
{
    glDeleteProgram(pId);
}


DrawShaderId GLCanvas::createShader(GLenum type,const char* code)
{
    DrawShaderId m_id = glCreateShader(type);
    CHECK_GL_ERROR;
    if (m_id)
    {
        const GLchar* ptr[] = {code};
        glShaderSource(m_id,sizeof(ptr)/sizeof(*ptr), ptr, NULL);
        glCompileShader(m_id);
        CHECK_GL_ERROR;
        //检查
        GLint compiled;
        glGetShaderiv ( m_id, GL_COMPILE_STATUS, &compiled );
        if ( !compiled )
        {
            GLint infoLen = 0;
            
            
            glGetShaderiv ( m_id, GL_INFO_LOG_LENGTH, &infoLen );
            
            if ( infoLen > 1 )
            {
                char infoLog[infoLen+1];
                memset(infoLog, 0, infoLen+1);
                
                glGetShaderInfoLog ( m_id, infoLen, NULL, infoLog );
                DM("Error compiling shader:\n%s", (const char*)infoLog);
            }
            
            glDeleteShader ( m_id );
            m_id=0;
            return 0;
        }
        return m_id;
    }
    return 0;
}

void GLCanvas::attachShader(DrawPrgId pId,DrawShaderId sId)
{
    glAttachShader(pId,sId);
}

void GLCanvas::detachShader(DrawPrgId pId,DrawShaderId sId)
{
    glDetachShader(pId, sId);
}

void GLCanvas::deleteShader(DrawShaderId sId)
{
    glDeleteShader(sId);
}


int GLCanvas::getUniform(DrawPrgId pId, const char* v)
{
    int index = glGetUniformLocation(pId,v);
    return index;
}

void GLCanvas::bindAttribute(DrawPrgId pId,const char * name, int location)
{
    glBindAttribLocation(pId,location,name);
    CHECK_GL_ERROR;
}

static GLuint s_VAO=-1;
void GLCanvas::bindVAO(DrawVAOId vaoId)
{
    if (s_VAO != vaoId)
    {
        s_VAO = vaoId;
        glBindVertexArray(vaoId);
    }
}

static int MAX_ATTRIBUTES = 16;
static uint32_t s_attributeFlags = 0;
void GLCanvas::enableVertexAttribs(uint32_t flags)
{
    for(int i=0; i < MAX_ATTRIBUTES; i++) {
        unsigned int bit = 1 << i;
        bool enabled = flags & bit;
        bool enabledBefore = s_attributeFlags & bit;
        if(enabled != enabledBefore) {
            if( enabled )
                glEnableVertexAttribArray(i);
            else
                glDisableVertexAttribArray(i);
        }
    }
    s_attributeFlags = flags;
}

void GLCanvas::vertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
    glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
}


void GLCanvas::setUniform1f(GLint location, GLfloat x)
{
    glUniform1f(location, x);
}

void GLCanvas::setUniform1i(GLint location, GLint x)
{
    glUniform1i(location, x);
}

void GLCanvas::setUniform2fv(GLint location, GLsizei count, GLfloat* x)
{
    glUniform2fv(location, count, x);
}

void GLCanvas::setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv(location,count,transpose,value);
}


void GLCanvas::drawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid *indices)
{
    glDrawElements(mode,count,type,indices);
}

void GLCanvas::checkError()
{
    GLint v = glGetError();
    if(v){
        DM("OpenGL 出错:%x\n%s",v);
    }
}

void GLCanvas::checkProgramError(GLProgram* program)
{
    GLint v = glGetError();
    if (v) {
        DM("Error GL:0x%x", v);
        char infoLog[128];
        memset(infoLog, 0, 128);
        
        glGetProgramInfoLog ( program->getProgramId(), 127, NULL, infoLog );
        DM("Error program:%s", (const char*)infoLog);
        
        for (int i=0; i< program->getShaderCount(); ++i)
        {
            GLShaderObject* obj = program->getShader(i);
            memset(infoLog, 0, 128);
            glGetShaderInfoLog ( obj->getId(), 127, NULL, infoLog );
            DM("Error shader:%s", (const char*)infoLog);
        }
    }
}

DE_END
