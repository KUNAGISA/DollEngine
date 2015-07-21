#include "TjsDictIterator.h"

TjsDictIterator::TjsDictIterator()
    :m_root_dict (null)
    ,m_root_iter(null)
    ,m_line_iter(null)
    ,m_current_iter(null)
    ,m_size(0)
{
}

void TjsDictIterator::begin(iTJSDispatch2* root)
{
    m_root_dict = dynamic_cast<tTJSDictionaryObject*>(root);
    if(m_root_dict)
    {
        m_root_iter = m_root_dict->Symbols;
        m_size = m_root_dict->HashSize;
        m_line_iter = m_root_iter->Next;
    }
}

bool TjsDictIterator::atEnd()
{
    return m_size <= 0;
}


bool TjsDictIterator::next()
{
    if(m_size <= 0)
        return false;
    if(m_line_iter)
    {
        if(m_line_iter->SymFlags & TJS_SYMBOL_USING)
        {
            m_current_iter = m_line_iter;
            m_line_iter = m_line_iter->Next;
            return true;
        }
        return false;
    }
    if(m_root_iter->SymFlags & TJS_SYMBOL_USING)
    {
        m_current_iter = m_root_iter;
        ++m_root_iter;
        m_line_iter = m_root_iter->Next;
        --m_size;
        return true;
    }
    else
    {
        ++m_root_iter;
        --m_size;
        return next();
    }
}

ttstr TjsDictIterator::key()
{
    if(m_current_iter == null) return "";
    return m_current_iter->GetName();
}

tTJSVariant TjsDictIterator::value()
{
    if(m_current_iter == null) return "";
    return *((tTJSVariant*)(&m_current_iter->Value));
}

NCB_REGISTER_CLASS_DIFFER(DictIterator,TjsDictIterator)
{
    NCB_CONSTRUCTOR(());
    NCB_METHOD(begin);
    NCB_METHOD(next);
    NCB_PROPERTY_RO(atEnd,atEnd);
    NCB_PROPERTY_RO(key,key);
    NCB_PROPERTY_RO(value,value);
};
