//
//  ErrorInfos.h
//  DollEngine
//
//  Created by DollStudio on 14-9-16.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ErrorInfos__
#define __DollEngine__ErrorInfos__

enum ERROR_INFOS
{
    NO_ERROR=0,
    UNKNOW_ERROR=1,
    
    ERROR_PaintEngine_INIT_FAILD_FRAME = 10,
    ERROR_PaintEngine_INIT_FAILD_RENDER,
    ERROR_PaintEngine_INIT_FAILD_DEPTH,
    
    ERROR_FILE_OPENFAIL_PATH_CANTFIND = 50,
    ERROR_FILE_OPENFAIL_DATA_READFAIL,
    
    ERROR_KAG_UNKONW = 60,
    ERROR_KAG_LABELKEY_NULL,
    ERROR_KAG_VALUE_STRING_ENDED,
    ERROR_KAG_TAG_ENDED,
    ERROR_KAG_LABEL_FIND_FAIL,
    ERROR_KAG_TAG_FIND_FAIL,
    ERROR_KAG_TOO_MANY_RETURN,
    ERROR_KAG_MACRONAME_EMPTY,
    ERROR_KAG_MACRO_NESTING,
    
    
    ERROR_COMP_OBJ_HAS_SAME_COMP = 100,
    ERROR_COMP_TYPE_TOUCH_NEED_MOUSEHANDLER,
    ERROR_COMP_TYPE_NOT_COMP,
    
    ERROR_FT_UNKNOW_FILE_FORMAT = 200,
    ERROR_FT_NO_TTF,
    ERROR_FT_USE_UNICODE_FAILD,
    ERROR_FT_SET_CHAR_SIZE_FAILD,
    ERROR_FT_UNKNOW,
    
    ERROR_OPENGL_UNKNOW = 1000,
    
};


extern const char* get_error_infos(ERROR_INFOS info);

#endif /* defined(__DollEngine__ErrorInfos__) */
