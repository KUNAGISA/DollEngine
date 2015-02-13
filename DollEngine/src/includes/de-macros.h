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
#pragma mark 通用宏

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

#define null NULL

#define CHECK_GL_ERROR de::gl::check_error()
#define ASSERT assert
#define DE_EXTERN extern

#define NAMESPACE_DE_GL \
namespace de { \
namespace gl {

#define NAMESPACE_DE_DEVICE \
namespace de { \
namespace device {

#define NAMESPACE_DE_END }\
}

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


#endif
