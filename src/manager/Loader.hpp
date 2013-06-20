#ifndef					__LOADER_HPP__
# define				__LOADER_HPP__

#include				"Exception.hh"
#include				"File.hpp"

template				<class T>
class					Loader
{
public:
  virtual				~Loader() {};
  virtual T				*load(const File &file, bool force = false)
  {
    throw LoadingFailed(file.getFullName(), "This loader doesn't support LOAD for this file type.");
    (void)force;
  }
  virtual void				save(const T *, const std::string &name)
  {
    throw LoadingFailed(name, "This loader doesn't support SAVE for this file type.");
  }
protected:
  Loader()
  {}
};

#endif					// __LOADER_HPP__
