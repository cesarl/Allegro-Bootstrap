#ifndef					__SINGLETON_HPP__
# define				__SINGLETON_HPP__

template				<class T>
class					Singleton
{
public :
  static T				&getInstance()
  {
    if (!that_)
      that_ = new T;

    return *that_;
  }
protected :
  Singleton() {}
  ~Singleton() {}
private :
  static T				*that_;
  Singleton(Singleton&);
  void operator =(Singleton&);
};

template				<class T>
T* Singleton<T>::that_ = NULL;

#endif					// __SINGLETON_HPP__
