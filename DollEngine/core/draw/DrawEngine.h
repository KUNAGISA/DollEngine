#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include "CoreTypes.h"
#include "SpriteFrame.h"
#include "Transform.h"
#include "Effect.h"

DE_BEGIN

class DrawEngine : public QOpenGLFunctions
{
public:
    enum EFFECT_PROGRAM{
        NORMAL_EFFECT =0,
    };
    
    DrawEngine();
    Shared(DrawEngine)
    virtual ~DrawEngine();
    
    void setContext(QOpenGLContext* v){m_context=v;}
    void initializeGL();
    void clearGL();
    void resizeGL(int width, int height);
    
    SpriteFrame* addImage(const QString& picKey,const QString& plist="");
    void initDefaultEffect();
    void addEffect(EFFECT_PROGRAM pm,Effect*);
    Effect* getEffect(EFFECT_PROGRAM pm);
    
    void draw(SpriteFrame* frame,Transform* trans,const GradientColor& color,Effect* effect);
    void removeSpriteFrameCache(SpriteFrame* frame);
    void removeTextureCache(Texture2D* frame);
protected:
    QMap<QString,QVariant > m_allPlist;
    QMap<QString,SpriteFrame*> m_allSpriteFrames;
    QMap<QString,Texture2D*> m_allTextures;
    Transform* m_deviceTrans;
    QMap<EFFECT_PROGRAM,Effect*> m_allEffects;
    QOpenGLBuffer m_vbo;
    QOpenGLContext* m_context;
};

DE_END

#endif // DRAWENGINE_H
