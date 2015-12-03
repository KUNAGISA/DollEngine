#ifndef TJSRTT_H
#define TJSRTT_H

#include "TjsBind.h"
#include "RTT.h"

TJS_NCB(RTT){}
void paint(tTJSVariant trans);
bool saveToFile(tTJSVariant path,tTJSVariant w,tTJSVariant h);
};


#endif // TJSRTT_H
