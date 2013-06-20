#ifndef					__SMART_POINTER_POLICIES_HPP__
#define					__SMART_POINTER_POLICIES_HPP__

#include				<cstdlib>
#include				"Exception.hh"

template				<class T>
class					ExternalRef
{
public:
  ExternalRef() : counter_(new int(1))
  {}

  T					*clone(T *ptr)
  {
    ++(*this->counter_);
    return ptr;
  }

  void					release(T *ptr)
  {
    if (--(this->counter_) == 0)
      {
	delete this->counter_;
	delete ptr;
      }
  }

  void					swap(ExternalRef &plc)
  {
    std::swap(plc.counter_, this->counter_);
  }

  int					getCounter() const
  {
    return *this->counter_;
  }
private:
  int					*counter_;
};

template				<class T>
class					InternalRef
{
public:
  InternalRef() : counter_(new int(1))
  {}

  static T				*clone(T *ptr)
  {
    std::cout << "lol" << std::endl;
    if (ptr)
      ptr->addRef();
    return ptr;
  }

  static void				release(T *ptr)
  {
    if (ptr)
      ptr->release();
  }

  static void				swap(InternalRef &)
  {
  }

  int					getCounter() const
  {
    return *this->counter_;
  }
private:
  int					*counter_;
};

#endif					// __SMART_POINTER_POLICIES_HPP__
