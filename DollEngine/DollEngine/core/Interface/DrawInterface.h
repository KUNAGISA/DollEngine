#ifndef DRAWINTERFACE_H
#define DRAWINTERFACE_H

#include "Types.h"

DE_BEGIN

class ImageData;

typedef GLuint DrawFBOId;//fbo手柄
typedef GLuint DrawTexId;//贴图手柄
typedef GLuint DrawActiveTexId;//生效的贴图

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
};

DE_END

#endif // DRAWINTERFACE_H
