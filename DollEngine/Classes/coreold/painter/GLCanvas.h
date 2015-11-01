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


class GLProgram;

class GLCanvas
{
public:
    GLCanvas();
    ~GLCanvas();
    Shared(GLCanvas);
    
    void initializeGL();
    void clearGL();
    void resizeGL();
    
    PROPERTY_RO(Transform*,GlobalTrans,m_globalTrans)
    
    PROPERTY(float,LayerWidth,m_layerWidth){m_layerWidth=v;}
    PROPERTY(float,LayerHeight,m_layerHeight){m_layerHeight=v;} //逻辑大小
    PROPERTY(float,LayerX,m_layerX){m_layerX=v;}
    PROPERTY(float,LayerY,m_layerY){m_layerY = v;}
    PROPERTY(float,LayerZoom,m_layerZoom){m_layerZoom=v;}
    
public:
    void blendFunc(GLenum src,GLenum dst);
    void addProgram(string pm,GLProgram*);
    GLProgram* getProgram(string pm);
    
public:
    void paint(PaintConfig& config);
protected:
    map<string,GLProgram*> m_allPrograms;
    bool m_initialized;
};

DE_END

#endif /* defined(__DEPainter__GLCanvas__) */
