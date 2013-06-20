#ifndef					__RESOURCE_MANAGER_HPP__
# define				__RESOURCE_MANAGER_HPP__

#include				<map>
#include				"Singleton.hpp"
#include				"Exception.hh"
#include				"ILogger.hh"
#include				"Resource.hh"
#include				"MediaManager.hpp"

class					ResourceManager : public Singleton<ResourceManager>
{
public:
  template				<class T>
  inline T				*get(const std::string &name) const
  {
    t_const_iter			it;

    it = this->list_.find(name);
    if (it != this->list_.end())
      {
	it->second->addRef();
	return static_cast<T*>(it->second);
      }
    MediaManager::getInstance().load<T>(name);
    return this->find<T>(name);
  }

  void					add(const std::string &name, Resource *resource, bool force = false)
  {
    Assert(resource != NULL);
    if (this->list_.find(name) != this->list_.end())
      {
	if (force)
	  {
	    *(this->list_[name]) = *resource;
	  }
	else
	  {
	    ILogger::log("%s : already loaded", name.c_str());
	  }
      }
    this->list_[name] = resource;
    resource->name_ = name;
  }

  void					remove(const std::string &name)
  {
    t_iter				it;

    it = this->list_.find(name);
    if (it == this->list_.end())
      {
	ILogger::log("%s : destroy called, but not loaded before", name.c_str());
	return;
      }
    this->list_.erase(it);
  }

  template				<class T>
  void					reload()
  {
    t_iter				it;

    it = this->list_.begin();
    while (it != this->list_.end())
      {
	if (dynamic_cast<T*>(it->second))
	  {
	    MediaManager::getInstance().load<T>(it->first, true);
	  }
	++it;
      }
  }
private:
  ResourceManager()
  {}

  virtual ~ResourceManager()
  {
    t_iter				it;

    it = this->list_.begin();
    while (it != this->list_.end())
      {
	ILogger::log("%s : has not been destroyed before exit the program.");
	delete it->second;
	++it;
      }
  }

  template				<class T>
  inline T				*find(const std::string &name) const
  {
    t_const_iter			it;

    it = this->list_.find(name);
    if (it != this->list_.end())
      {
	return static_cast<T*>(it->second);
      }
    throw LoadingFailed(name, "This file is not loaded and can not be found.");
    return NULL;
  }

private:
  friend class Singleton<ResourceManager>;
  typedef std::map<std::string, Resource*>::iterator		t_iter;
  typedef std::map<std::string, Resource*>::const_iterator	t_const_iter;
  std::map<std::string, Resource*>	list_;
};

#endif					// __RESOURCE_MANAGER_HPP__
