#ifndef SINGLEPROGRAM_H
#define SINGLEPROGRAM_H

#include "PaintProgram.h"

DE_BEGIN

class SingleProgram : public PaintProgram
{
public:
    SingleProgram();
    bool init();
    const char* getShader_V();
    const char* getShader_F();
};

DE_END

#endif // SINGLEPROGRAM_H
