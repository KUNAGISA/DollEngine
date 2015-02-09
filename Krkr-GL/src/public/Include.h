//
//  Include.h
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef DollEngine_Include_h
#define DollEngine_Include_h


#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <stack>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>

//OS_IOS 在Prefix.pch里define
#ifdef OS_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif

#ifdef OS_MAC
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#endif

#include "kazmath.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

/**命名规范说明
 * 类名和文件名一致（包括上面说的大小写一致），例如 UserController类的文件命名是UserController.h， InfoModel类的文件名是InfoModel.h， 并且不同的类库的类命名有一定的规范；
 * 配置文件等其他类库文件之外的一般是以.h、.cpp为后缀（第三方引入的不做要求）；
 * 公共函数的命名使用小写字母和下划线的方式，例如 get_client_ip；
 * 方法的命名使用驼峰法，并且首字母小写或者使用下划线“_”，例如 getUserName，_parseType，通常下划线开头的方法属于私有方法；
 * 静态方法以首字母大写，例如 XXX::GetInterface
 * 属性的命名使用驼峰法，m_开头并且首字母小写或者使用下划线“_”，例如 m_tableName、_instance，通常下划线开头的属性属于私有属性；
 * 以双下划线“__”打头的函数或方法作为魔法方法，例如 __call 和 __autoload；
 * 常量以大写字母和下划线命名，例如 HAS_ONE和 MANY_TO_MANY；
 * 配置参数以大写字母和下划线命名，例如HTML_CACHE_ON；
 * 语言变量以大写字母和下划线命名，例如MY_LANG，以下划线打头的语言变量通常用于系统语言变量，例如 _CLASS_NOT_EXIST_；
 * 对变量的命名没有强制的规范，可以根据团队规范来进行；
 * 数据表和字段采用小写加下划线方式命名，并注意字段名不要以下划线开头，例如 think_user 表和 user_name字段是正确写法，类似 _username 这样的数据表字段可能会被过滤。
 */


#endif
