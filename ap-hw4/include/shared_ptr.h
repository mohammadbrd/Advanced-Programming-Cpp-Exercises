#ifndef SHARED_PTR
#define SHARED_PTR

template<typename T>

class SharedPtr
{
public:
    SharedPtr();
    SharedPtr(T* _p);
    SharedPtr(SharedPtr &ptr);
    ~SharedPtr();
    explicit operator bool();
    T* get();
    T& operator*();
    T* operator->();
    SharedPtr<T>& operator=(const SharedPtr& p);
    void reset();
    void reset(T* p);
    int use_count();
private:
    T* _p;
    int* count_shared;
};

template <typename T>
SharedPtr<T> make_shared(T inpt)
{
    return SharedPtr<T> {new T{inpt}};
}

#include "shared_ptr.hpp"
#endif //SHARED_PTR