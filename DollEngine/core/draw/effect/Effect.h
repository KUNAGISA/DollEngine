#ifndef EFFECT_H
#define EFFECT_H

#include "CoreTypes.h"

DE_BEGIN

class Effect : public QOpenGLShaderProgram
{
public:
    Effect();
    virtual ~Effect();
    virtual bool init()=0;
    virtual void actived()=0;
};

DE_END

#endif // EFFECT_H
