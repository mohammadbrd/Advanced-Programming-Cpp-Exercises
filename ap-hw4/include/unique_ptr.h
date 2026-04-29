#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template<typename T>

class UniquePtr
{
public:
    UniquePtr();
    UniquePtr(T* _p);
    UniquePtr(UniquePtr &ptr) = delete;
    ~UniquePtr();
    explicit operator bool();
    T* get();
    T& operator*();
    T* operator->();
    T* release();
    UniquePtr<T>& operator=(const UniquePtr& p) = delete;
    void reset();
    void reset(T* p);
private:
    T* _p;
};

template <typename T>
UniquePtr<T> make_unique(T inpt)
{
    return UniquePtr<T> {new T{inpt}};
}

#include "unique_ptr.hpp"
#endif //UNIQUE_PTR