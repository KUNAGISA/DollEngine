#include "TjsColorRect.h"

NCB_REGISTER_CLASS_DIFFER(ColorRect, TjsColorRect)
{
    TJS_FACTORY
    NCB_METHOD(loadSize);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
};

