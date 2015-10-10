#ifndef DRAWINTERFACE_H
#define DRAWINTERFACE_H

#include "CoreTypes.h"

DE_BEGIN

class ImageData;

typedef GLuint DrawFBOId;//fbo手柄
typedef GLuint DrawTexId;//贴图手柄
typedef GLuint DrawActiveTexId;//生效的贴图
typedef GLuint DrawPrgId; //program
typedef GLuint DrawShaderId; //shader
typedef GLuint DrawVAOId;

typedef GLsizei DrawSizeI;
typedef GLclampf DrawClampF;
typedef GLbitfield DrawMask;

#ifdef __QT__
class DrawInterface : public QOpenGLFunctions
#else
class DrawInterface
#endif
{
public:
    DrawInterface(){}
    static DrawInterface* GetInstance();
    
    void deleteFBO(DrawSizeI n, const DrawFBOId * framebuffers);
    DrawFBOId createFBO(DrawTexId texId );
    void switchFBO(DrawFBOId* oldFBO,DrawFBOId newFBO);
    
    void clearColor(DrawMask mask,DrawClampF red,DrawClampF green,DrawClampF blue,DrawClampF alpha);
    
    DrawTexId loadTexture(void* data, int width,int height);
    void bindTexture(DrawActiveTexId aid,DrawTexId bid);
    void deleteTexture(DrawSizeI count,DrawTexId* texId);
    
    DrawPrgId createProgram();
    bool linkProgram(DrawPrgId pId);
    void useProgram(DrawPrgId pId);
    void deleteProgram(DrawPrgId pId);
    
    DrawShaderId createShader(GLenum type,const char* code);
    void attachShader(DrawPrgId pId,DrawShaderId sId);
    void detachShader(DrawPrgId pId,DrawShaderId sId);
    void deleteShader(DrawShaderId sId);
    
    int getUniform(DrawPrgId pId, const char* v);
    void bindAttribute(DrawPrgId pId,const char * name, int location);
    void bindVAO(DrawVAOId vaoId);
    void enableVertexAttribs(uint32_t flags);
    void vertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr);
    
    void setUniform1f(GLint location, GLfloat x);
    void setUniform1i(GLint location, GLint x);
    void setUniform2fv(GLint location, GLsizei count, GLfloat* x);
    void setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    
    void drawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid *indices);
};

DE_END

#endif // DRAWINTERFACE_H
