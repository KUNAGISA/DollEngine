#ifndef NORMALEFFECT_H
#define NORMALEFFECT_H

#include "Effect.h"

DE_BEGIN
class NormalEffect : public Effect
{
public:
    NormalEffect();
    ~NormalEffect();
    bool init();
    void actived();
    
};
DE_END
#endif // NORMALEFFECT_H
