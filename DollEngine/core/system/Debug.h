#ifndef DEBUG_H
#define DEBUG_H

#include "Macros.h"

DE_BEGIN

enum DEBUG_MSG
{
    ERROR_IMAGE_LOAD_FAILD = 1001,
    ERROR_FILE_EXIST_FAILD = 1002,
};

class Debug
{
public:
    Debug();
    virtual ~Debug();
    
    static QString throwMsg(DEBUG_MSG error,const QString& p1="");
    static QString throwMsg(const QString& v){return v;}
};

DE_END

#endif // DEBUG_H
