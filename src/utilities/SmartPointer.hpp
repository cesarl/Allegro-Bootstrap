#ifndef					__SMART_POINTER_HPP__
#define					__SMART_POINTER_HPP__

#include				<cstdlib>
#include				"Exception.hh"
#include				"SmartPointerPolicies.hpp"

template				<class T, template <class> class Ownership = ExternalRef>
class					SmartPtr : public Ownership<T>
{
public:
  SmartPtr() :
    data_(NULL)
  {
  }

  SmartPtr(const SmartPtr<T, Ownership> & o) :
    Ownership<T>(o),
    data_(this->clone(o.data_))
  {
  }

  SmartPtr(T *ptr) :
    data_(ptr)
  {}

  virtual ~SmartPtr()
  {
    Ownership<T>::release(this->data_);
  }

  void					swap(SmartPtr<T, Ownership> &ptr)
  {
    Ownership<T>::swap(ptr);
    std::swap(this->data_, ptr.data_);
  }

  T					&operator *()
  {
    Assert(this->data_ != NULL);
    return *(this->data_);
  }

  T					*operator ->()
  {
    Assert(this->data_ != NULL);
    return this->data_;
  }

  const SmartPtr<T, Ownership>		&operator =(SmartPtr<T, Ownership> &ptr)
  {
    SmartPtr<T, Ownership>(ptr).swap(*this);

    return *this;
  }

  const SmartPtr<T, Ownership>		&operator =(T *ptr)
  {
    if (this->data_ != ptr)
      {
	SmartPtr<T, Ownership>(ptr).swap(*this);
      }
    return *this;
  }

  operator T*() const
  {
    return this->data_;
  }

private:
  T					*data_;
};

template				<class T, template <class> class Ownership>
T					*&getPtr(SmartPtr<T, Ownership> &ptr)
{
  return ptr.data_;
}


#endif					// __SMART_POINTER_HPP__
