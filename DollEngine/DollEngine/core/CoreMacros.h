//
//  Macros.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef DollEngine_Macros_h
#define DollEngine_Macros_h

#include <string>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <algorithm>
#include <sys/time.h>
#include "kazmath.h"

using namespace std;

#define PI 3.14159265358979323846264338327950288
#define DEFFONT L"WenQuanYi Micro Hei"
#define DEFFONTSIZE 24
#define DM(...) DE::Console::GetInstance()->log(DE::String::fromFormat(__VA_ARGS__))
#define EM DE::Console::GetInstance()->throwMsg
#define ASSERT assert

#define DE_BEGIN namespace DE {
#define DE_END }

#define DESystem DE::System::GetInstance()

#define NEED_REDRAW DE::System::NeedRedraw = true;

#define Shared(type) static type* GetInstance() \
{\
static type* _instance=NULL; \
if(!_instance) { \
_instance = new type(); } \
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

#define TRANSFORM_PROPERTY_FUNC(NAME,VALUE) \
void set##NAME(float v) \
{\
if (m_transform) { \
m_transform->set##VALUE(v);\
NEED_REDRAW;\
}\
}\
float get##NAME()\
{\
if (m_transform) {\
return m_transform->get##VALUE();\
}\
return 0;\
}

#define SAFF_DELETE(OBJ) if(OBJ){delete OBJ;OBJ=NULL;}
#define SAFF_DELETE_ARRAY(OBJ) if(OBJ){delete[] OBJ;OBJ=NULL;}
#define SAFF_RETAIN(OBJ) if(OBJ){OBJ->retain();}
#define SAFF_RELEASE(OBJ) if(OBJ){OBJ->release();OBJ=NULL;}

#pragma mark -
#pragma mark GL相关

#ifdef OS_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#define	glClearDepth glClearDepthf
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define glGenVertexArrays glGenVertexArraysOES
#define glBindVertexArray glBindVertexArrayOES
#define glMapBuffer glMapBufferOES
#define glUnmapBuffer glUnmapBufferOES

#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES

#elif defined(OS_MAC)
#include <OpenGL/gl.h>

#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#define glGenVertexArrays  glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glClearDepthf glClearDepth
#define glDepthRangef glDepthRange
#define glReleaseShaderCompiler(xxx)

#elif defined(__QT__)
#include <QtOpenGL>
#include <QOpenGLFunctions_4_5_Core>
#endif

#define CHECK_GL_ERROR PaintEngine::GetInstance()->checkError();
#define CHECK_PROGRAM_ERROR(ID) PaintEngine::GetInstance()->checkProgramError(ID);

#endif
