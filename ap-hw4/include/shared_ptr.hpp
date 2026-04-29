#include "Shared_ptr.h"
///////////Constructor////////////////////////////////////////////////////////////////
template<typename T>
SharedPtr<T> :: SharedPtr() : _p{nullptr}, count_shared{new int(0)}{};
///////////Constructor////////////////////////////////////////////////////////////////
template<typename T>
SharedPtr<T> :: SharedPtr(T* p) : _p{p}, count_shared{new int(1)}{};
///////////Copy Constructor///////////////////////////////////////////////////////////
template<typename T>
SharedPtr<T> :: SharedPtr(SharedPtr &ptr)
{
    _p = ptr.get();
    count_shared = ptr.count_shared;
    (*count_shared)++;
}
///////////Deconstructor//////////////////////////////////////////////////////////////
template<typename T>
SharedPtr<T> :: ~SharedPtr() 
{
    (*count_shared)--;
    if (*count_shared == 0)
    {
        if (nullptr != _p)
        {
            delete _p;
            _p = nullptr;
        }
    }
}
///////////Operator*//////////////////////////////////////////////////////////////////
template<typename T>
T& SharedPtr<T>::operator*()
{
    return (*_p);
}
///////////Operator->/////////////////////////////////////////////////////////////////
template<typename T>
T* SharedPtr<T>::operator->()
{
    return _p;
}
///////////Operator=//////////////////////////////////////////////////////////////////
template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& p)
{
    if(_p == p._p)
        return *this;
    _p = p._p;
    count_shared = p.count_shared;
    (*count_shared)++;
    return(*this);
}
///////////Get////////////////////////////////////////////////////////////////////////
template<typename T>
T* SharedPtr<T>::get()
{
    return _p;
}
///////////reset1/////////////////////////////////////////////////////////////////////
template<typename T>
void SharedPtr<T>::reset()
{
    delete _p;
    _p = nullptr;
    (*count_shared) = 0;
}
///////////reset2/////////////////////////////////////////////////////////////////////
template<typename T>
void SharedPtr<T>::reset(T* p)
{
    delete _p;
    _p = p;
    (*count_shared) = 1;
}
///////////Operator Bool/////////////////////////////////////////////////////////////
template<typename T>
SharedPtr<T>::operator bool()
{
    if(_p)
        return true;
    return false;
}
///////////use_count////////////////////////////////////////////////////////////////
template<typename T>
int SharedPtr<T>::use_count()
{
    return *count_shared;
}