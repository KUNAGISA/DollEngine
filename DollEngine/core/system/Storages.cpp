#include "Storages.h"
#include "Device.h"

DE_BEGIN

Storages::Storages()
{
    
}

Storages::~Storages()
{
    
}

QString Storages::getFullPath(const QString& path)
{
    if(exists(path))
    {
        return path;
    }
    QString fullPath = Device::GetInstance()->getDataPath()+"/"+path;
    if(exists(fullPath))
    {
        return fullPath;
    }
    return "";
}

bool Storages::exists(const QString& path)
{
    return QFile::exists(path);
}

DE_END
