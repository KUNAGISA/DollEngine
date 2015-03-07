//
//  fdv_res.h
//  FileDataToVariable
//  该文件由FDV工具生成
//  工具Git地址 https://github.com/DollStudio/FileDataToVariable
//
//

#ifndef __FileDataToVariable__fdv_res__
#define __FileDataToVariable__fdv_res__

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

namespace fdv
{
class FDV_Data
{
public:
    FDV_Data():bytes(),size(0){}
    ~FDV_Data(){if (bytes) {delete [] bytes;}}
    const unsigned char* bytes;
    size_t size;
    std::string path;
};
extern const unsigned char* read_file(const char* path,long& length);
}

#endif /* defined(__FileDataToVariable__fdv_res__) */
