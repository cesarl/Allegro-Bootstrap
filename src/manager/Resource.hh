#ifndef					__RESOURCE_HH__
# define				__RESOURCE_HH__

#include				<string>

class					Resource
{
public:
  Resource(const std::string & name = "", bool force = false);
  virtual ~Resource();
  const std::string			&getName() const;
  void					addRef();
  int					release();
  int					getCounter() const;
  void					operator=(Resource &o);
private:
  // copy forbiden
  Resource(Resource &o);
private:
  std::string				name_;
  int					counter_;
  // autorize ResourceManager to modify it's name
  friend class ResourceManager;
};

#endif					// __RESOURCE_HH__
