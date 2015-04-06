#include "Debug.h"

DE_BEGIN
Debug::Debug()
{
    
}

Debug::~Debug()
{
    
}

QString Debug::throwMsg(DEBUG_MSG error,const QString& p1)
{
    switch (error) {
    case ERROR_IMAGE_LOAD_FAILD:
        return QString("图片资源加载失败:%1").arg(p1);
        break;
    case ERROR_FILE_EXIST_FAILD:
        return QString("文件未找到:%1").arg(p1);
        break;
    default:
        return QString("未知错误");
        break;
    }
}

DE_END
