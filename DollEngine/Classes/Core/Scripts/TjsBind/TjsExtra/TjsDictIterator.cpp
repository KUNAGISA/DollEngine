#include "TjsDictIterator.h"

TjsDictIterator::TjsDictIterator()
    :m_root_iter(NULL)
    ,m_next_iter(NULL)
    ,m_current_iter(NULL)
    ,m_root_dict(NULL)
    ,m_size(0)
{
}

TjsDictIterator::~TjsDictIterator()
{
}

void TjsDictIterator::begin(tTJSVariant root)
{
    m_root_dict = dynamic_cast<tTJSDictionaryObject*>(root.AsObjectNoAddRef());
    if(m_root_dict)
    {
        m_root_iter = m_root_dict->Symbols;
        m_size = m_root_dict->HashSize;
    }
}

void TjsDictIterator::begin(tTJSVariant* root)
{
    if (m_root_dict) {
        m_root_dict->Release();
    }
    m_root_dict = dynamic_cast<tTJSDictionaryObject*>(root->AsObjectNoAddRef());
    if(m_root_dict)
    {
        m_root_iter = m_root_dict->Symbols;
        m_size = m_root_dict->HashSize;
    }
}//刚刚被设置的时候,都是定位于begin的

bool TjsDictIterator::atEnd()
{
    return m_size <= 0;
}


bool TjsDictIterator::next()
{
    if(m_size <= 0)
        return false;
    if (!m_current_iter) {
        m_current_iter = m_root_iter;
        m_next_iter = m_current_iter->Next;
        if (!m_current_iter->SymFlags&TJS_SYMBOL_USING) {
            return next();
        }
        return true;
    }
    if (m_next_iter) {
        m_current_iter = m_next_iter;
        m_next_iter = m_current_iter->Next;
        return true;
    }
    else
    {
        ++m_root_iter;
        --m_size;
        if(m_size <= 0)
            return false;
        m_current_iter = m_root_iter;
        m_next_iter = m_current_iter->Next;
        if (!m_current_iter->SymFlags&TJS_SYMBOL_USING) {
            return next();
        }
        return true;
    }
}

const tjs_char * TjsDictIterator::key()
{
    if(m_current_iter == NULL) return L"";
    return m_current_iter->GetName();
}

static tTJSVariant_S tTJSVariant_SEmpty;

tTJSVariant_S& TjsDictIterator::value()
{
    if(m_current_iter == NULL) return tTJSVariant_SEmpty;
    return m_current_iter->Value;
}

//NCB_REGISTER_CLASS_DIFFER(DictIterator,TjsDictIterator)
//{
//    NCB_CONSTRUCTOR(());
//    NCB_METHOD(begin);
//    NCB_METHOD(next);
//    NCB_PROPERTY_RO(atEnd,atEnd);
//    NCB_PROPERTY_RO(key,key);
//    NCB_PROPERTY_RO(value,value);
//};
