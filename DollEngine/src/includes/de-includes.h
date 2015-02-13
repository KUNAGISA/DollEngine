//
//  de-includes.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef DollEngine_de_includes_h
#define DollEngine_de_includes_h

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


#endif
