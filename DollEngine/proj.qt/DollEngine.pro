#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T11:26:02
#
#-------------------------------------------------

QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DollEngine
TEMPLATE = app

CONFIG += c++11

DEFINES += __QT__

INCLUDEPATH += \
../DollEngine/core \
../DollEngine/Core/Base \
../DollEngine/Core/Component \
../DollEngine/Core/Data/ValueUnits \
../DollEngine/Core/Data/FileUnits \
../DollEngine/Core/Data/ImageUnits \
../DollEngine/Core/EventManager \
../DollEngine/Core/KAGParser \
../DollEngine/Core/Painter \
../DollEngine/Core/Painter/Program \
../DollEngine/Core/Painter/PaintComponent \
../DollEngine/Core/Scripts \
../DollEngine/Core/Scripts/TjsExtra \
../DollEngine/Core/Widget \
../DollEngine/Core/Interface \
../DollEngine/Lib/kazmath/include/kazmath \
../DollEngine/Lib/kazmath/include/kazmath/GL \
../DollEngine/Lib/ncbind \
../DollEngine/Lib/onig \
../DollEngine/Lib/tjs2 \

SOURCES += main.cpp\
    QtConsole.cpp \
    QtWindow.cpp \
    ../DollEngine/Lib/msg/apple/MsgLoad.cpp \
    ../DollEngine/Lib/ncbind/ncbind.cpp \
    ../DollEngine/Lib/tjs2/tjs.cpp \
    ../DollEngine/Lib/tjs2/tjs.tab.cpp \
    ../DollEngine/Lib/tjs2/tjsArray.cpp \
    ../DollEngine/Lib/tjs2/tjsBinarySerializer.cpp \
    ../DollEngine/Lib/tjs2/tjsByteCodeLoader.cpp \
    ../DollEngine/Lib/tjs2/tjsCompileControl.cpp \
    ../DollEngine/Lib/tjs2/tjsConfig.cpp \
    ../DollEngine/Lib/tjs2/tjsConstArrayData.cpp \
    ../DollEngine/Lib/tjs2/tjsDate.cpp \
    ../DollEngine/Lib/tjs2/tjsdate.tab.cpp \
    ../DollEngine/Lib/tjs2/tjsDateParser.cpp \
    ../DollEngine/Lib/tjs2/tjsDebug.cpp \
    ../DollEngine/Lib/tjs2/tjsDictionary.cpp \
    ../DollEngine/Lib/tjs2/tjsDisassemble.cpp \
    ../DollEngine/Lib/tjs2/tjsError.cpp \
    ../DollEngine/Lib/tjs2/tjsException.cpp \
    ../DollEngine/Lib/tjs2/tjsGlobalStringMap.cpp \
    ../DollEngine/Lib/tjs2/tjsInterCodeExec.cpp \
    ../DollEngine/Lib/tjs2/tjsInterCodeGen.cpp \
    ../DollEngine/Lib/tjs2/tjsInterface.cpp \
    ../DollEngine/Lib/tjs2/tjsLex.cpp \
    ../DollEngine/Lib/tjs2/tjsMath.cpp \
    ../DollEngine/Lib/tjs2/tjsMessage.cpp \
    ../DollEngine/Lib/tjs2/tjsMT19937ar-cok.cpp \
    ../DollEngine/Lib/tjs2/tjsNamespace.cpp \
    ../DollEngine/Lib/tjs2/tjsNative.cpp \
    ../DollEngine/Lib/tjs2/tjsObject.cpp \
    ../DollEngine/Lib/tjs2/tjsObjectExtendable.cpp \
    ../DollEngine/Lib/tjs2/tjsOctPack.cpp \
    ../DollEngine/Lib/tjs2/tjspp.tab.cpp \
    ../DollEngine/Lib/tjs2/tjsRandomGenerator.cpp \
    ../DollEngine/Lib/tjs2/tjsRegExp.cpp \
    ../DollEngine/Lib/tjs2/tjsScriptBlock.cpp \
    ../DollEngine/Lib/tjs2/tjsScriptCache.cpp \
    ../DollEngine/Lib/tjs2/tjsString.cpp \
    ../DollEngine/Lib/tjs2/tjsUtils.cpp \
    ../DollEngine/Lib/tjs2/tjsVariant.cpp \
    ../DollEngine/Lib/tjs2/tjsVariantString.cpp \
    ../DollEngine/Lib/kazmath/src/GL/mat4stack.c \
    ../DollEngine/Lib/kazmath/src/GL/matrix.c \
    ../DollEngine/Lib/kazmath/src/aabb.c \
    ../DollEngine/Lib/kazmath/src/mat3.c \
    ../DollEngine/Lib/kazmath/src/mat4.c \
    ../DollEngine/Lib/kazmath/src/neon_matrix_impl.c \
    ../DollEngine/Lib/kazmath/src/plane.c \
    ../DollEngine/Lib/kazmath/src/quaternion.c \
    ../DollEngine/Lib/kazmath/src/ray2.c \
    ../DollEngine/Lib/kazmath/src/utility.c \
    ../DollEngine/Lib/kazmath/src/vec2.c \
    ../DollEngine/Lib/kazmath/src/vec3.c \
    ../DollEngine/Lib/kazmath/src/vec4.c \
    ../DollEngine/Lib/onig/enc/ascii.c \
    ../DollEngine/Lib/onig/enc/big5.c \
    ../DollEngine/Lib/onig/enc/cp1251.c \
    ../DollEngine/Lib/onig/enc/euc_jp.c \
    ../DollEngine/Lib/onig/enc/euc_kr.c \
    ../DollEngine/Lib/onig/enc/euc_tw.c \
    ../DollEngine/Lib/onig/enc/gb18030.c \
    ../DollEngine/Lib/onig/enc/iso8859_1.c \
    ../DollEngine/Lib/onig/enc/iso8859_10.c \
    ../DollEngine/Lib/onig/enc/iso8859_11.c \
    ../DollEngine/Lib/onig/enc/iso8859_13.c \
    ../DollEngine/Lib/onig/enc/iso8859_14.c \
    ../DollEngine/Lib/onig/enc/iso8859_15.c \
    ../DollEngine/Lib/onig/enc/iso8859_16.c \
    ../DollEngine/Lib/onig/enc/iso8859_2.c \
    ../DollEngine/Lib/onig/enc/iso8859_3.c \
    ../DollEngine/Lib/onig/enc/iso8859_4.c \
    ../DollEngine/Lib/onig/enc/iso8859_5.c \
    ../DollEngine/Lib/onig/enc/iso8859_6.c \
    ../DollEngine/Lib/onig/enc/iso8859_7.c \
    ../DollEngine/Lib/onig/enc/iso8859_8.c \
    ../DollEngine/Lib/onig/enc/iso8859_9.c \
    ../DollEngine/Lib/onig/enc/koi8.c \
    ../DollEngine/Lib/onig/enc/koi8_r.c \
    ../DollEngine/Lib/onig/enc/mktable.c \
    ../DollEngine/Lib/onig/enc/sjis.c \
    ../DollEngine/Lib/onig/enc/unicode.c \
    ../DollEngine/Lib/onig/enc/utf16_be.c \
    ../DollEngine/Lib/onig/enc/utf16_le.c \
    ../DollEngine/Lib/onig/enc/utf32_be.c \
    ../DollEngine/Lib/onig/enc/utf32_le.c \
    ../DollEngine/Lib/onig/enc/utf8.c \
    ../DollEngine/Lib/onig/regcomp.c \
    ../DollEngine/Lib/onig/regenc.c \
    ../DollEngine/Lib/onig/regerror.c \
    ../DollEngine/Lib/onig/regexec.c \
    ../DollEngine/Lib/onig/regext.c \
    ../DollEngine/Lib/onig/reggnu.c \
    ../DollEngine/Lib/onig/regparse.c \
    ../DollEngine/Lib/onig/regposerr.c \
    ../DollEngine/Lib/onig/regposix.c \
    ../DollEngine/Lib/onig/regsyntax.c \
    ../DollEngine/Lib/onig/regtrav.c \
    ../DollEngine/Lib/onig/regversion.c \
    ../DollEngine/Lib/onig/st.c \
    ../DollEngine/Core/Base/Storages.cpp \
    ../DollEngine/Core/Base/System.cpp \
    ../DollEngine/Core/Data/ValueUnits/Color.cpp \
    ../DollEngine/Core/Data/ValueUnits/Transform.cpp \
    ../DollEngine/Core/Data/ValueUnits/CoreString.cpp \
    ../DollEngine/Core/Data/FileUnits/FileInfo.cpp \
    ../DollEngine/Core/Data/FileUnits/IOData.cpp \
    ../DollEngine/Core/Data/ImageUnits/PictureData.cpp \
    ../DollEngine/Core/Data/ImageUnits/ImageInfo.cpp \
    ../DollEngine/Core/Data/ImageUnits/CharacterInfo.cpp \
    ../DollEngine/Core/KAGParser/KAGController.cpp \
    ../DollEngine/Core/KAGParser/KAGLabel.cpp \
    ../DollEngine/Core/KAGParser/KAGParser.cpp \
    ../DollEngine/Core/KAGParser/KAGStorage.cpp \
    ../DollEngine/Core/KAGParser/KAGTag.cpp \
    ../DollEngine/Core/Painter/Program/GrowProgram.cpp \
    ../DollEngine/Core/Painter/Program/NormalProgram.cpp \
    ../DollEngine/Core/Painter/Program/PaintShader.cpp \
    ../DollEngine/Core/Painter/PaintEngine.cpp \
    ../DollEngine/Core/Scripts/TjsExtra/TjsDictIterator.cpp \
    ../DollEngine/Core/Scripts/TjsExtra/TjsSet.cpp \
    ../DollEngine/Core/Scripts/JsonParser.cpp \
    ../DollEngine/Core/Scripts/ScriptEngine.cpp \
    ../DollEngine/Core/Scripts/TjsBind.cpp \
    ../DollEngine/Core/Widget/Window.cpp \
    ../DollEngine/Core/Widget/Console.cpp \
    ../DollEngine/Core/Platform/qt/PictureData-Qt.cpp \
    ../DollEngine/Core/Scripts/TjsExtra/TjsScripts.cpp \
    ../DollEngine/Core/Scripts/TjsExtra/TjsStorages.cpp \
    ../DollEngine/Core/Scripts/TjsExtra/TjsSystem.cpp \
    ../DollEngine/Core/Scripts/TjsExtra/TjsConsole.cpp \
    ../DollEngine/Core/Platform/qt/System-Qt.cpp \
    ../DollEngine/Core/Base/SystemDelegate.cpp \
    ../DollEngine/Core/Platform/qt/Audio-Qt.cpp \
    ../DollEngine/Core/Platform/gl/PaintEngine-GL.cpp \
    ../DollEngine/Core/Painter/Program/PaintProgram.cpp \ 
    ../DollEngine/Core/Painter/PaintComponent/Character.cpp \
    ../DollEngine/Core/Painter/PaintComponent/RTT.cpp \
    ../DollEngine/Core/Data/ImageUnits/Texture.cpp \
    ../DollEngine/Core/Painter/PaintComponent/Image.cpp \
    ../DollEngine/Core/Painter/PaintComponent/ColorRect.cpp \
    ../DollEngine/Core/Data/ValueUnits/CoreStructs.cpp

HEADERS  += \
    QtConsole.h \
    QtWindow.h \
    ../DollEngine/Lib/kazmath/include/kazmath/GL/mat4stack.h \
    ../DollEngine/Lib/kazmath/include/kazmath/GL/matrix.h \
    ../DollEngine/Lib/kazmath/include/kazmath/aabb.h \
    ../DollEngine/Lib/kazmath/include/kazmath/kazmath.h \
    ../DollEngine/Lib/kazmath/include/kazmath/mat3.h \
    ../DollEngine/Lib/kazmath/include/kazmath/mat4.h \
    ../DollEngine/Lib/kazmath/include/kazmath/neon_matrix_impl.h \
    ../DollEngine/Lib/kazmath/include/kazmath/plane.h \
    ../DollEngine/Lib/kazmath/include/kazmath/quaternion.h \
    ../DollEngine/Lib/kazmath/include/kazmath/ray2.h \
    ../DollEngine/Lib/kazmath/include/kazmath/utility.h \
    ../DollEngine/Lib/kazmath/include/kazmath/vec2.h \
    ../DollEngine/Lib/kazmath/include/kazmath/vec3.h \
    ../DollEngine/Lib/kazmath/include/kazmath/vec4.h \
    ../DollEngine/Lib/msg/apple/string_table_en.h \
    ../DollEngine/Lib/msg/apple/string_table_jp.h \
    ../DollEngine/Lib/msg/apple/string_table_resource.h \
    ../DollEngine/Lib/ncbind/ncb_foreach.h \
    ../DollEngine/Lib/ncbind/ncb_invoke.hpp \
    ../DollEngine/Lib/ncbind/ncbind.hpp \
    ../DollEngine/Lib/onig/config.h \
    ../DollEngine/Lib/onig/oniggnu.h \
    ../DollEngine/Lib/onig/onigposix.h \
    ../DollEngine/Lib/onig/oniguruma.h \
    ../DollEngine/Lib/onig/regenc.h \
    ../DollEngine/Lib/onig/regint.h \
    ../DollEngine/Lib/onig/regparse.h \
    ../DollEngine/Lib/onig/st.h \
    ../DollEngine/Lib/tjs2/tjs.h \
    ../DollEngine/Lib/tjs2/tjs.tab.h \
    ../DollEngine/Lib/tjs2/tjs.tab.hpp \
    ../DollEngine/Lib/tjs2/tjsArray.h \
    ../DollEngine/Lib/tjs2/tjsBinarySerializer.h \
    ../DollEngine/Lib/tjs2/tjsByteCodeLoader.h \
    ../DollEngine/Lib/tjs2/tjsCommHead.h \
    ../DollEngine/Lib/tjs2/tjsCompileControl.h \
    ../DollEngine/Lib/tjs2/tjsConfig.h \
    ../DollEngine/Lib/tjs2/tjsConstArrayData.h \
    ../DollEngine/Lib/tjs2/tjsDate.h \
    ../DollEngine/Lib/tjs2/tjsdate.tab.h \
    ../DollEngine/Lib/tjs2/tjsdate.tab.hpp \
    ../DollEngine/Lib/tjs2/tjsDateParser.h \
    ../DollEngine/Lib/tjs2/tjsDebug.h \
    ../DollEngine/Lib/tjs2/tjsDictionary.h \
    ../DollEngine/Lib/tjs2/tjsError.h \
    ../DollEngine/Lib/tjs2/tjsErrorDefs.h \
    ../DollEngine/Lib/tjs2/tjsErrorInc.h \
    ../DollEngine/Lib/tjs2/tjsException.h \
    ../DollEngine/Lib/tjs2/tjsGlobalStringMap.h \
    ../DollEngine/Lib/tjs2/tjsHashSearch.h \
    ../DollEngine/Lib/tjs2/tjsInterCodeExec.h \
    ../DollEngine/Lib/tjs2/tjsInterCodeGen.h \
    ../DollEngine/Lib/tjs2/tjsInterface.h \
    ../DollEngine/Lib/tjs2/tjsLex.h \
    ../DollEngine/Lib/tjs2/tjsMath.h \
    ../DollEngine/Lib/tjs2/tjsMessage.h \
    ../DollEngine/Lib/tjs2/tjsMT19937ar-cok.h \
    ../DollEngine/Lib/tjs2/tjsNamespace.h \
    ../DollEngine/Lib/tjs2/tjsNative.h \
    ../DollEngine/Lib/tjs2/tjsObject.h \
    ../DollEngine/Lib/tjs2/tjsObjectExtendable.h \
    ../DollEngine/Lib/tjs2/tjsOctPack.h \
    ../DollEngine/Lib/tjs2/tjspp.tab.h \
    ../DollEngine/Lib/tjs2/tjspp.tab.hpp \
    ../DollEngine/Lib/tjs2/tjsRandomGenerator.h \
    ../DollEngine/Lib/tjs2/tjsRegExp.h \
    ../DollEngine/Lib/tjs2/tjsScriptBlock.h \
    ../DollEngine/Lib/tjs2/tjsScriptCache.h \
    ../DollEngine/Lib/tjs2/tjsString.h \
    ../DollEngine/Lib/tjs2/tjsTypes.h \
    ../DollEngine/Lib/tjs2/tjsUtils.h \
    ../DollEngine/Lib/tjs2/tjsVariant.h \
    ../DollEngine/Lib/tjs2/tjsVariantString.h \
    ../DollEngine/Core/Base/System.h \
    ../DollEngine/Core/Base/Storages.h \
    ../DollEngine/Core/Data/ValueUnits/Color.h \
    ../DollEngine/Core/Data/ValueUnits/Transform.h \
    ../DollEngine/Core/Data/FileUnits/FileInfo.h \
    ../DollEngine/Core/Data/FileUnits/IOData.h \
    ../DollEngine/Core/Data/ImageUnits/PictureData.h \
    ../DollEngine/Core/Data/ImageUnits/ImageInfo.h \
    ../DollEngine/Core/Data/ImageUnits/CharacterInfo.h \
    ../DollEngine/Core/KAGParser/KAGController.h \
    ../DollEngine/Core/KAGParser/KAGLabel.h \
    ../DollEngine/Core/KAGParser/KAGParser.h \
    ../DollEngine/Core/KAGParser/KAGStorage.h \
    ../DollEngine/Core/KAGParser/KAGTag.h \
    ../DollEngine/Core/Painter/Program/GrowProgram.h \
    ../DollEngine/Core/Painter/Program/NormalProgram.h \
    ../DollEngine/Core/Painter/Program/PaintShader.h \
    ../DollEngine/Core/Painter/Program/PaintProgram.h \ 
    ../DollEngine/Core/Painter/PaintComponent/Character.h \
    ../DollEngine/Core/Painter/PaintComponent/RTT.h\
    ../DollEngine/Core/Painter/PaintEngine.h \
    ../DollEngine/Core/Scripts/TjsExtra/TjsDictIterator.h \
    ../DollEngine/Core/Scripts/TjsExtra/TjsSet.h \
    ../DollEngine/Core/Scripts/JsonParser.h \
    ../DollEngine/Core/Scripts/ScriptEngine.h \
    ../DollEngine/Core/Scripts/TjsBind.h \
    ../DollEngine/Core/Widget/Console.h \
    ../DollEngine/Core/Widget/Window.h \
    ../DollEngine/Core/CoreMacros.h \
    ../DollEngine/Core/Data/ValueUnits/CoreString.h \
    ../DollEngine/Core/Scripts/TjsExtra/TjsScripts.h \
    ../DollEngine/Core/Scripts/TjsExtra/TjsStorages.h \
    ../DollEngine/Core/Scripts/TjsExtra/TjsSystem.h \
    ../DollEngine/Core/Scripts/TjsExtra/TjsConsole.h \
    ../DollEngine/Core/Base/SystemDelegate.h \
    ../DollEngine/Core/Base/Audio.h \ 
    ../DollEngine/Core/Data/ImageUnits/Texture.h \
    ../DollEngine/Core/Painter/PaintComponent/Image.h \
    ../DollEngine/Core/Painter/PaintComponent/ColorRect.h \
    ../DollEngine/Core/Data/ValueUnits/CoreStructs.h \
    ../DollEngine/Core/CoreTypes.h

FORMS  += QtConsole.ui

RESOURCES += \
    font.qrc

