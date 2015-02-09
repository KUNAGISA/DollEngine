//
//  ErrorInfos.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-16.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "ErrorInfos.h"
#include "Functions.h"

static map<ERROR_INFOS,string>* s_error_infos = new map<ERROR_INFOS,string>();

const char* get_error_infos(ERROR_INFOS info)
{
    map<ERROR_INFOS,string>& infos = *s_error_infos;
    if(s_error_infos->size() == 0)
    {
        infos[NO_ERROR]
        = "无错误";
        infos[UNKNOW_ERROR]
        = "未知错误";
        infos[ERROR_PaintEngine_INIT_FAILD_FRAME]
        = "无法创建默认的frame buffer";
        infos[ERROR_PaintEngine_INIT_FAILD_RENDER]
        = "无法创建默认的render buffer";
        infos[ERROR_PaintEngine_INIT_FAILD_DEPTH]
        = "无法创建默认的depth buffer";
        
        infos[ERROR_COMP_OBJ_HAS_SAME_COMP]
        = "SetCOM时，对象已经合并了目标类型组件%ls";
        infos[ERROR_COMP_TYPE_TOUCH_NEED_MOUSEHANDLER]
        = "组件%ls要在touch时触发，必须继承MouseHandler";
        infos[ERROR_COMP_TYPE_NOT_COMP]
        = "参数不是组件类型";
        
        infos[ERROR_FILE_OPENFAIL_PATH_CANTFIND]
        = "读取文件失败，路径未找到:%ls";
        infos[ERROR_FILE_OPENFAIL_DATA_READFAIL]
        = "读取文件失败，数据读取失败:%ls";
        
        infos[ERROR_KAG_UNKONW]
        = "(#%d)KAG解析发生未知错误";
        infos[ERROR_KAG_LABELKEY_NULL]
        = "(#%d)标签的名字不能为空";
        infos[ERROR_KAG_VALUE_STRING_ENDED]
        = "(#%d)字符串没有结尾，可能缺少 \" 或 \' ，请检查";
        infos[ERROR_KAG_TAG_ENDED]
        = "(#%d)Tag没有结尾，可能缺少 ] ，请检查";
        infos[ERROR_KAG_LABEL_FIND_FAIL]
        = "(#%d)未找到名为%ls的标签";
        infos[ERROR_KAG_TAG_FIND_FAIL]
        = "(#%d)未找到名为%ls的指令";
        infos[ERROR_KAG_TOO_MANY_RETURN]
        = "(#%d)过多的Return指令，与Call指令无法形成对应";
        infos[ERROR_KAG_MACRONAME_EMPTY]
        = "(#%d)Macro的name属性为空";
        infos[ERROR_KAG_MACRO_NESTING]
        = "(#%d)Macro不可嵌套";
        
        
        infos[ERROR_FT_UNKNOW_FILE_FORMAT]
        = "可以打开和读这个文件，但不支持它的字体格式";
        infos[ERROR_FT_NO_TTF]
        = "字体文件%ls打开失败，或损坏，或不存在";
        infos[ERROR_FT_USE_UNICODE_FAILD]
        = "字体工具使用unicode失败";
        infos[ERROR_FT_SET_CHAR_SIZE_FAILD]
        = "字体工具设置字体大小失败";
        infos[ERROR_FT_UNKNOW]
        = "FreeType发生错误，错误代码:%d";
        
        
        infos[ERROR_OPENGL_UNKNOW]
        = "OpenGL发生错误，错误代码:0x%04x";
        
    }
    auto iter = s_error_infos->find(info);
    if(iter == s_error_infos->end())
    {
        return infos[UNKNOW_ERROR].c_str();
    }
    return iter->second.c_str();
}
