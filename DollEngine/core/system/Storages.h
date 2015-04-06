#ifndef STORAGES_H
#define STORAGES_H

#include "CoreTypes.h"

DE_BEGIN
class Storages
{
public:
    Storages();
    virtual ~Storages();
    Shared(Storages)
    
    QString getFullPath(const QString& path);
    bool exists(const QString& path);
};
DE_END
#endif // STORAGES_H
