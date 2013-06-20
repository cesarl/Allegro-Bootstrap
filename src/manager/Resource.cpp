#include				"Resource.hh"
#include				"ResourceManager.hpp"

Resource::Resource(const std::string & name, bool force) :
  name_(name),
  counter_(1)
{
  ResourceManager::getInstance().add(name, this, force);
}

Resource::~Resource()
{
  ResourceManager::getInstance().remove(this->name_);
}

const std::string			&Resource::getName() const
{
  return this->name_;
}

void					Resource::addRef()
{
  ++(this->counter_);
}

int					Resource::release()
{
  int					c = --(this->counter_);

  if (c <= 0)
    delete this;
  return c;
}

void					Resource::operator=(Resource &o)
{
  this->counter_ = o.counter_;
}

int					Resource::getCounter() const
{
  return this->counter_;
}
