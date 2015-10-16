//
//  GLCanvas.h
//  DEPainter
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DEPainter__GLCanvas__
#define __DEPainter__GLCanvas__

#include "CoreUnits.h"
#include "Transform.h"

DE_BEGIN

class ImageData;
class GLProgram;

#ifdef __QT__
class GLCanvas : public QOpenGLFunctions_4_5_Core
#else
class GLCanvas
#endif
{
public:
    static GLCanvas* GetInstance();
    GLCanvas();
    ~GLCanvas();
    
public:
    void addProgram(String pm,GLProgram*);
    GLProgram* getProgram(String pm);
    
    void initializeGL();
    void resizeGL(float desktopw,float desktoph);
    void paint(PaintConfig& config);
    
public:
    void initialize();
    void blendFunc(DrawBlendId src,DrawBlendId dst);
    
    void deleteFBO(DrawSizeI n, const DrawFBOId * framebuffers);
    DrawFBOId createFBO(DrawTexId texId );
    void switchFBO(DrawFBOId* oldFBO,DrawFBOId newFBO);
    
    void clearColor(DrawMask mask,DrawClampF red,DrawClampF green,DrawClampF blue,DrawClampF alpha);
    
    DrawTexId loadTexture(void* data, int width,int height);
    void bindTexture(DrawActiveTexId aid,DrawTexId bid);
    void deleteTexture(DrawSizeI count,DrawTexId* texId);
    void readPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid *pixels);
    
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
    
    void checkError();
    void checkProgramError(GLProgram* program);
public:
    PROPERTY_RO(Transform*,GlobalTrans,m_globalTrans)
    
    PROPERTY(float,LayerWidth,m_layerWidth){m_layerWidth=v;}
    PROPERTY(float,LayerHeight,m_layerHeight){m_layerHeight=v;} //逻辑大小
    PROPERTY(float,LayerX,m_layerX){m_layerX=v;}
    PROPERTY(float,LayerY,m_layerY){m_layerY = v;}
    PROPERTY(float,LayerZoom,m_layerZoom){m_layerZoom=v;}
    
protected:
    map<String,GLProgram*> m_allPrograms;
    bool m_initialized;
};

DE_END

#endif /* defined(__DEPainter__GLCanvas__) */
