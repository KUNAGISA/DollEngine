#ifndef TJSITERATOR_H
#define TJSITERATOR_H

#include "TjsBind.h"

/*
 * ** using in tjs: **
 * var iter = Iterator(dict);
 * while(iter.next())
 * {
 *      dm(iter.key()+"="+iter.value());
 * }
 */

class TjsDictIterator
{
public:
    TjsDictIterator();
    ~TjsDictIterator();
    void begin(tTJSVariant root);//刚刚被设置的时候,都是定位于begin的
    void begin(tTJSVariant* root);//刚刚被设置的时候,都是定位于begin的
    bool atEnd();
    bool next();//当移动后等于end时,return false
    const tjs_char * key();
    tTJSVariant_S& value();
private:
    tTJSDictionaryObject* m_root_dict;
    tTJSDictionaryObject::tTJSSymbolData * m_root_iter;
    tTJSDictionaryObject::tTJSSymbolData * m_next_iter;
    tTJSDictionaryObject::tTJSSymbolData * m_current_iter;
    int m_size;
};

#endif // TJSITERATOR_H
