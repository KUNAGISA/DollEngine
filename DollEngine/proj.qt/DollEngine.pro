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

DEFINES += __QT__ \
UNICODE

INCLUDEPATH += \
../Classes/core \
../Classes/Core/Base \
../Classes/Core/Component \
../Classes/Core/Data/ValueUnits \
../Classes/Core/Data/FileUnits \
../Classes/Core/Data/ImageUnits \
../Classes/Core/EventManager \
../Classes/Core/KAGParser \
../Classes/Core/Painter \
../Classes/Core/Painter/Program \
../Classes/Core/Painter/PaintComponent \
../Classes/Core/Scripts \
../Classes/Core/Scripts/TjsBind \
../Classes/Core/Scripts/TjsBind/TjsClasses \
../Classes/Core/Scripts/TjsBind/TjsExtra \
../Classes/Core/Scripts/TjsBind/TjsSingleton \
../Classes/Core/Widget \
../Classes/Core/Interface \
../Classes/Lib/kazmath/include/kazmath \
../Classes/Lib/kazmath/include/kazmath/GL \
../Classes/Lib/ncbind \
../Classes/Lib/onig \
../Classes/Lib/tjs2 \

SOURCES += main.cpp\
    ../Classes/Lib/msg/apple/MsgLoad.cpp \
    ../Classes/Lib/ncbind/ncbind.cpp \
    ../Classes/Lib/tjs2/tjs.cpp \
    ../Classes/Lib/tjs2/tjs.tab.cpp \
    ../Classes/Lib/tjs2/tjsArray.cpp \
    ../Classes/Lib/tjs2/tjsBinarySerializer.cpp \
    ../Classes/Lib/tjs2/tjsByteCodeLoader.cpp \
    ../Classes/Lib/tjs2/tjsCompileControl.cpp \
    ../Classes/Lib/tjs2/tjsConfig.cpp \
    ../Classes/Lib/tjs2/tjsConstArrayData.cpp \
    ../Classes/Lib/tjs2/tjsDate.cpp \
    ../Classes/Lib/tjs2/tjsdate.tab.cpp \
    ../Classes/Lib/tjs2/tjsDateParser.cpp \
    ../Classes/Lib/tjs2/tjsDebug.cpp \
    ../Classes/Lib/tjs2/tjsDictionary.cpp \
    ../Classes/Lib/tjs2/tjsDisassemble.cpp \
    ../Classes/Lib/tjs2/tjsError.cpp \
    ../Classes/Lib/tjs2/tjsException.cpp \
    ../Classes/Lib/tjs2/tjsGlobalStringMap.cpp \
    ../Classes/Lib/tjs2/tjsInterCodeExec.cpp \
    ../Classes/Lib/tjs2/tjsInterCodeGen.cpp \
    ../Classes/Lib/tjs2/tjsInterface.cpp \
    ../Classes/Lib/tjs2/tjsLex.cpp \
    ../Classes/Lib/tjs2/tjsMath.cpp \
    ../Classes/Lib/tjs2/tjsMessage.cpp \
    ../Classes/Lib/tjs2/tjsMT19937ar-cok.cpp \
    ../Classes/Lib/tjs2/tjsNamespace.cpp \
    ../Classes/Lib/tjs2/tjsNative.cpp \
    ../Classes/Lib/tjs2/tjsObject.cpp \
    ../Classes/Lib/tjs2/tjsObjectExtendable.cpp \
    ../Classes/Lib/tjs2/tjsOctPack.cpp \
    ../Classes/Lib/tjs2/tjspp.tab.cpp \
    ../Classes/Lib/tjs2/tjsRandomGenerator.cpp \
    ../Classes/Lib/tjs2/tjsRegExp.cpp \
    ../Classes/Lib/tjs2/tjsScriptBlock.cpp \
    ../Classes/Lib/tjs2/tjsScriptCache.cpp \
    ../Classes/Lib/tjs2/tjsString.cpp \
    ../Classes/Lib/tjs2/tjsUtils.cpp \
    ../Classes/Lib/tjs2/tjsVariant.cpp \
    ../Classes/Lib/tjs2/tjsVariantString.cpp \
    ../Classes/Lib/kazmath/src/GL/mat4stack.c \
    ../Classes/Lib/kazmath/src/GL/matrix.c \
    ../Classes/Lib/kazmath/src/aabb.c \
    ../Classes/Lib/kazmath/src/mat3.c \
    ../Classes/Lib/kazmath/src/mat4.c \
    ../Classes/Lib/kazmath/src/neon_matrix_impl.c \
    ../Classes/Lib/kazmath/src/plane.c \
    ../Classes/Lib/kazmath/src/quaternion.c \
    ../Classes/Lib/kazmath/src/ray2.c \
    ../Classes/Lib/kazmath/src/utility.c \
    ../Classes/Lib/kazmath/src/vec2.c \
    ../Classes/Lib/kazmath/src/vec3.c \
    ../Classes/Lib/kazmath/src/vec4.c \
    ../Classes/Lib/onig/enc/ascii.c \
    ../Classes/Lib/onig/enc/big5.c \
    ../Classes/Lib/onig/enc/cp1251.c \
    ../Classes/Lib/onig/enc/euc_jp.c \
    ../Classes/Lib/onig/enc/euc_kr.c \
    ../Classes/Lib/onig/enc/euc_tw.c \
    ../Classes/Lib/onig/enc/gb18030.c \
    ../Classes/Lib/onig/enc/iso8859_1.c \
    ../Classes/Lib/onig/enc/iso8859_10.c \
    ../Classes/Lib/onig/enc/iso8859_11.c \
    ../Classes/Lib/onig/enc/iso8859_13.c \
    ../Classes/Lib/onig/enc/iso8859_14.c \
    ../Classes/Lib/onig/enc/iso8859_15.c \
    ../Classes/Lib/onig/enc/iso8859_16.c \
    ../Classes/Lib/onig/enc/iso8859_2.c \
    ../Classes/Lib/onig/enc/iso8859_3.c \
    ../Classes/Lib/onig/enc/iso8859_4.c \
    ../Classes/Lib/onig/enc/iso8859_5.c \
    ../Classes/Lib/onig/enc/iso8859_6.c \
    ../Classes/Lib/onig/enc/iso8859_7.c \
    ../Classes/Lib/onig/enc/iso8859_8.c \
    ../Classes/Lib/onig/enc/iso8859_9.c \
    ../Classes/Lib/onig/enc/koi8.c \
    ../Classes/Lib/onig/enc/koi8_r.c \
    ../Classes/Lib/onig/enc/mktable.c \
    ../Classes/Lib/onig/enc/sjis.c \
    ../Classes/Lib/onig/enc/unicode.c \
    ../Classes/Lib/onig/enc/utf16_be.c \
    ../Classes/Lib/onig/enc/utf16_le.c \
    ../Classes/Lib/onig/enc/utf32_be.c \
    ../Classes/Lib/onig/enc/utf32_le.c \
    ../Classes/Lib/onig/enc/utf8.c \
    ../Classes/Lib/onig/regcomp.c \
    ../Classes/Lib/onig/regenc.c \
    ../Classes/Lib/onig/regerror.c \
    ../Classes/Lib/onig/regexec.c \
    ../Classes/Lib/onig/regext.c \
    ../Classes/Lib/onig/reggnu.c \
    ../Classes/Lib/onig/regparse.c \
    ../Classes/Lib/onig/regposerr.c \
    ../Classes/Lib/onig/regposix.c \
    ../Classes/Lib/onig/regsyntax.c \
    ../Classes/Lib/onig/regtrav.c \
    ../Classes/Lib/onig/regversion.c \
    ../Classes/Lib/onig/st.c \
    ../Classes/Core/Base/Storages.cpp \
    ../Classes/Core/Base/System.cpp \
    ../Classes/Core/Data/ValueUnits/Color.cpp \
    ../Classes/Core/Data/ValueUnits/Transform.cpp \
    ../Classes/Core/Data/ValueUnits/CoreString.cpp \
    ../Classes/Core/Data/FileUnits/FileInfo.cpp \
    ../Classes/Core/Data/FileUnits/IOData.cpp \
    ../Classes/Core/Data/ImageUnits/PictureData.cpp \
    ../Classes/Core/Data/ImageUnits/ImageInfo.cpp \
    ../Classes/Core/Data/ImageUnits/CharacterInfo.cpp \
    ../Classes/Core/KAGParser/KAGController.cpp \
    ../Classes/Core/KAGParser/KAGLabel.cpp \
    ../Classes/Core/KAGParser/KAGParser.cpp \
    ../Classes/Core/KAGParser/KAGStorage.cpp \
    ../Classes/Core/KAGParser/KAGTag.cpp \
    ../Classes/Core/Painter/Program/GrowProgram.cpp \
    ../Classes/Core/Painter/Program/NormalProgram.cpp \
    ../Classes/Core/Painter/Program/PaintShader.cpp \
    ../Classes/Core/Painter/PaintEngine.cpp \
    ../Classes/Core/Scripts/JsonParser.cpp \
    ../Classes/Core/Scripts/ScriptEngine.cpp \
    ../Classes/Core/Widget/Window.cpp \
    ../Classes/Core/Widget/Console.cpp \
    ../Classes/Core/Platform/qt/PictureData-Qt.cpp \
    ../Classes/Core/Platform/qt/System-Qt.cpp \
    ../Classes/Core/Base/SystemDelegate.cpp \
    ../Classes/Core/Platform/qt/Audio-Qt.cpp \
    ../Classes/Core/Painter/Program/PaintProgram.cpp \ 
    ../Classes/Core/Painter/PaintComponent/Character.cpp \
    ../Classes/Core/Painter/PaintComponent/RTT.cpp \
    ../Classes/Core/Data/ImageUnits/Texture.cpp \
    ../Classes/Core/Painter/PaintComponent/Image.cpp \
    ../Classes/Core/Painter/PaintComponent/ColorRect.cpp \
    ../Classes/Core/Data/ValueUnits/CoreStructs.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsAudio.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsCharacter.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsKAGController.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsWindow.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsExtra/TjsDictIterator.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsExtra/TjsSet.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsConsole.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsScripts.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsStorages.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsSystem.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsBind.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsImage.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsColorRect.cpp \
    QtWindow.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsSystemDelegate.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsTransform.cpp \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsRTT.cpp \
    ConsoleFind.cpp \
    QtConsole.cpp

HEADERS  += \
    ../Classes/Lib/kazmath/include/kazmath/GL/mat4stack.h \
    ../Classes/Lib/kazmath/include/kazmath/GL/matrix.h \
    ../Classes/Lib/kazmath/include/kazmath/aabb.h \
    ../Classes/Lib/kazmath/include/kazmath/kazmath.h \
    ../Classes/Lib/kazmath/include/kazmath/mat3.h \
    ../Classes/Lib/kazmath/include/kazmath/mat4.h \
    ../Classes/Lib/kazmath/include/kazmath/neon_matrix_impl.h \
    ../Classes/Lib/kazmath/include/kazmath/plane.h \
    ../Classes/Lib/kazmath/include/kazmath/quaternion.h \
    ../Classes/Lib/kazmath/include/kazmath/ray2.h \
    ../Classes/Lib/kazmath/include/kazmath/utility.h \
    ../Classes/Lib/kazmath/include/kazmath/vec2.h \
    ../Classes/Lib/kazmath/include/kazmath/vec3.h \
    ../Classes/Lib/kazmath/include/kazmath/vec4.h \
    ../Classes/Lib/msg/apple/string_table_en.h \
    ../Classes/Lib/msg/apple/string_table_jp.h \
    ../Classes/Lib/msg/apple/string_table_resource.h \
    ../Classes/Lib/ncbind/ncb_foreach.h \
    ../Classes/Lib/ncbind/ncb_invoke.hpp \
    ../Classes/Lib/ncbind/ncbind.hpp \
    ../Classes/Lib/onig/config.h \
    ../Classes/Lib/onig/oniggnu.h \
    ../Classes/Lib/onig/onigposix.h \
    ../Classes/Lib/onig/oniguruma.h \
    ../Classes/Lib/onig/regenc.h \
    ../Classes/Lib/onig/regint.h \
    ../Classes/Lib/onig/regparse.h \
    ../Classes/Lib/onig/st.h \
    ../Classes/Lib/tjs2/tjs.h \
    ../Classes/Lib/tjs2/tjs.tab.h \
    ../Classes/Lib/tjs2/tjs.tab.hpp \
    ../Classes/Lib/tjs2/tjsArray.h \
    ../Classes/Lib/tjs2/tjsBinarySerializer.h \
    ../Classes/Lib/tjs2/tjsByteCodeLoader.h \
    ../Classes/Lib/tjs2/tjsCommHead.h \
    ../Classes/Lib/tjs2/tjsCompileControl.h \
    ../Classes/Lib/tjs2/tjsConfig.h \
    ../Classes/Lib/tjs2/tjsConstArrayData.h \
    ../Classes/Lib/tjs2/tjsDate.h \
    ../Classes/Lib/tjs2/tjsdate.tab.h \
    ../Classes/Lib/tjs2/tjsdate.tab.hpp \
    ../Classes/Lib/tjs2/tjsDateParser.h \
    ../Classes/Lib/tjs2/tjsDebug.h \
    ../Classes/Lib/tjs2/tjsDictionary.h \
    ../Classes/Lib/tjs2/tjsError.h \
    ../Classes/Lib/tjs2/tjsErrorDefs.h \
    ../Classes/Lib/tjs2/tjsErrorInc.h \
    ../Classes/Lib/tjs2/tjsException.h \
    ../Classes/Lib/tjs2/tjsGlobalStringMap.h \
    ../Classes/Lib/tjs2/tjsHashSearch.h \
    ../Classes/Lib/tjs2/tjsInterCodeExec.h \
    ../Classes/Lib/tjs2/tjsInterCodeGen.h \
    ../Classes/Lib/tjs2/tjsInterface.h \
    ../Classes/Lib/tjs2/tjsLex.h \
    ../Classes/Lib/tjs2/tjsMath.h \
    ../Classes/Lib/tjs2/tjsMessage.h \
    ../Classes/Lib/tjs2/tjsMT19937ar-cok.h \
    ../Classes/Lib/tjs2/tjsNamespace.h \
    ../Classes/Lib/tjs2/tjsNative.h \
    ../Classes/Lib/tjs2/tjsObject.h \
    ../Classes/Lib/tjs2/tjsObjectExtendable.h \
    ../Classes/Lib/tjs2/tjsOctPack.h \
    ../Classes/Lib/tjs2/tjspp.tab.h \
    ../Classes/Lib/tjs2/tjspp.tab.hpp \
    ../Classes/Lib/tjs2/tjsRandomGenerator.h \
    ../Classes/Lib/tjs2/tjsRegExp.h \
    ../Classes/Lib/tjs2/tjsScriptBlock.h \
    ../Classes/Lib/tjs2/tjsScriptCache.h \
    ../Classes/Lib/tjs2/tjsString.h \
    ../Classes/Lib/tjs2/tjsTypes.h \
    ../Classes/Lib/tjs2/tjsUtils.h \
    ../Classes/Lib/tjs2/tjsVariant.h \
    ../Classes/Lib/tjs2/tjsVariantString.h \
    ../Classes/Core/Base/System.h \
    ../Classes/Core/Base/Storages.h \
    ../Classes/Core/Data/ValueUnits/Color.h \
    ../Classes/Core/Data/ValueUnits/Transform.h \
    ../Classes/Core/Data/FileUnits/FileInfo.h \
    ../Classes/Core/Data/FileUnits/IOData.h \
    ../Classes/Core/Data/ImageUnits/PictureData.h \
    ../Classes/Core/Data/ImageUnits/ImageInfo.h \
    ../Classes/Core/Data/ImageUnits/CharacterInfo.h \
    ../Classes/Core/KAGParser/KAGController.h \
    ../Classes/Core/KAGParser/KAGLabel.h \
    ../Classes/Core/KAGParser/KAGParser.h \
    ../Classes/Core/KAGParser/KAGStorage.h \
    ../Classes/Core/KAGParser/KAGTag.h \
    ../Classes/Core/Painter/Program/GrowProgram.h \
    ../Classes/Core/Painter/Program/NormalProgram.h \
    ../Classes/Core/Painter/Program/PaintShader.h \
    ../Classes/Core/Painter/Program/PaintProgram.h \ 
    ../Classes/Core/Painter/PaintComponent/Character.h \
    ../Classes/Core/Painter/PaintComponent/RTT.h\
    ../Classes/Core/Painter/PaintEngine.h \
    ../Classes/Core/Scripts/JsonParser.h \
    ../Classes/Core/Scripts/ScriptEngine.h \
    ../Classes/Core/Widget/Console.h \
    ../Classes/Core/Widget/Window.h \
    ../Classes/Core/CoreMacros.h \
    ../Classes/Core/Data/ValueUnits/CoreString.h \
    ../Classes/Core/Base/SystemDelegate.h \
    ../Classes/Core/Base/Audio.h \ 
    ../Classes/Core/Data/ImageUnits/Texture.h \
    ../Classes/Core/Painter/PaintComponent/Image.h \
    ../Classes/Core/Painter/PaintComponent/ColorRect.h \
    ../Classes/Core/Data/ValueUnits/CoreStructs.h \
    ../Classes/Core/CoreTypes.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsAudio.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsCharacter.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsKAGController.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsWindow.h \
    ../Classes/Core/Scripts/TjsBind/TjsExtra/TjsDictIterator.h \
    ../Classes/Core/Scripts/TjsBind/TjsExtra/TjsSet.h \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsConsole.h \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsScripts.h \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsStorages.h \
    ../Classes/Core/Scripts/TjsBind/TjsSingleton/TjsSystem.h \
    ../Classes/Core/Scripts/TjsBind/TjsBind.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsImage.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsColorRect.h \
    QtWindow.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsSystemDelegate.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsTransform.h \
    ../Classes/Core/Scripts/TjsBind/TjsClasses/TjsRTT.h \
    ConsoleFind.h \
    QtConsole.h

FORMS  += \
    QtWindow.ui \
    ConsoleFind.ui \
    QtConsole.ui

RESOURCES +=

