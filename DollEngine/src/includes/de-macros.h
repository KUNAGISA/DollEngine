//
//  de-macros.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef DollEngine_de_macros_h
#define DollEngine_de_macros_h

#include "de-includes.h"

#pragma mark -
#pragma mark 通用

#ifdef OS_IOS

#define	glClearDepth				glClearDepthf
#define glDeleteVertexArrays		glDeleteVertexArraysOES
#define glGenVertexArrays			glGenVertexArraysOES
#define glBindVertexArray			glBindVertexArrayOES
#define glMapBuffer					glMapBufferOES
#define glUnmapBuffer				glUnmapBufferOES
#define glBindVertexArrayAPPLE      glBindVertexArray
#define GL_RGBA8                    GL_RGBA8_OES

#define GL_DEPTH24_STENCIL8			GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY				GL_WRITE_ONLY_OES

#endif

#ifdef UNICODE

#define de_string wstring
#define de_char wchar_t
#define de_w(x) L##x

#endif
#define de_var TJS::tTJSVariant

#define null NULL

#define CHECK_GL_ERROR de::gl::check_error()
#define ASSERT assert
#define DE_EXTERN extern
#define DM de::debug::message
#define EM de::debug::e_message

#define INNER_W (de::device::get_inner_width()/2)
#define INNER_H (de::device::get_inner_height()/2)
#define PI 3.14159265358979323846264338327950288
#define DEFFONT de_w("WenQuanYi Micro Hei")

#define DELETE_OBJ(OBJ) if(OBJ){delete OBJ;OBJ=null;}
#define DELETE_ARRAY(OBJ) if(OBJ){delete[] OBJ;OBJ=null;}

#define LOAD_FILE(data,path,ret) \
de::Data* data=null;\
{\
de::storage::File file;\
file.setFileName(path);\
if (!file.open())\
{\
    EM(E_STORAGE_FILE_NOT_OPEN,path.c_str());\
    return ret;\
}\
data = file.getData();\
}

#pragma mark -
#pragma mark 属性与单例

#define Shared(type) static type* GetInstance() \
{\
static type* _instance=NULL;\
if(!_instance) \
_instance = new type(); \
return  _instance; \
}

#define PROPERTY(type,func,value) \
protected:\
type value;\
public:\
type get##func(){return value;}\
virtual void set##func(type v)

#define PROPERTY_CONST(type,func,value) \
protected:\
type value;\
public:\
type get##func(){return value;}\
virtual void set##func(const type & v)

#define PROPERTY_RO(type,func,value) \
protected:\
type value;\
public:\
type get##func(){return value;}


#pragma mark -
#pragma mark 命名空间

#define NAMESPACE_DE_BEGIN \
namespace de {

#define NAMESPACE_DE_GL \
namespace de { \
namespace gl {

#define NAMESPACE_DE_DEVICE \
namespace de { \
namespace device {

#define NAMESPACE_DE_STORAGE \
namespace de { \
namespace storage {

#define NAMESPACE_DE_PLATFORM \
namespace de { \
namespace platform {

#define NAMESPACE_DE_SCRIPT \
namespace de { \
namespace script {

#define NAMESPACE_DE_DEBUG \
namespace de { \
namespace debug {

#define NAMESPACE_DE_PAINTER \
namespace de { \
namespace painter {

#define NAMESPACE_DE_FONTS \
namespace de { \
namespace fonts {

#define NAMESPACE_DE_END }

#define NAMESPACE_DE_END2 }\
}

#endif
