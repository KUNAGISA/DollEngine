//
//  Macros.h
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef DollEngine_Macros_h
#define DollEngine_Macros_h

#include "Include.h"

#pragma mark -
#pragma mark 通用宏

#define __DEBUG_LANGUAGE_EN 1
#define __DEBUG_LANGUAGE_JP 2
#define __DEBUG_LANGUAGE_CH 3

#define __DEBUG_LANGUAGE_ __DEBUG_LANGUAGE_EN

#define UNICODE 1

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


#define CHECK_GL_ERROR check_opengl_error()
#define CHECK_FT_ERROR if (ft_err) {EM(ERROR_FT_UNKNOW,ft_err);}

#define null NULL

#define Shared(type) static type* GetInstance() \
{\
static type* _instance=NULL;\
if(!_instance) \
_instance = new type(); \
return  _instance; \
}

#define Instance(Type) if(Type::GetInstance()) Type::GetInstance()

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

#define DM debug_message
#define EM error_message
#define THROW_EM(...) EM(__VA_ARGS__);ASSERT(NULL);
#define THROW_DM(...) DM(__VA_ARGS__);ASSERT(NULL);
#define ASSERT assert

#define SAFF_DELETE_NULL(OBJ) if(OBJ){delete OBJ;OBJ=null;}
#define SAFF_DELETE_ARRAY(OBJ) if(OBJ){delete[] OBJ;OBJ=null;}
#define SAFF_RETAIN(OBJ) if(OBJ){OBJ->retain();}
#define SAFF_RELEASE(OBJ) if(OBJ){OBJ->release();}
#define SAFF_RELEASE_NULL(OBJ) if(OBJ){OBJ->release();OBJ=null;}

#define NEED_REVISIT System::GetInstance()->setNeedReVisit(true)
#define IS_NEED_REVISIT System::GetInstance()->getNeedReVisit()

#define Window_W (Window::GetInstance()->getInnerWidth()/2)
#define Window_H (Window::GetInstance()->getInnerHeight()/2)
#define PI 3.14159265358979323846264338327950288
#define DEFFONT L"WenQuanYi Micro Hei"

#endif
