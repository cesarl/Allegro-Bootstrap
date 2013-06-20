#ifndef					__OPTION_VALUE_HH__
# define				__OPTION_VALUE_HH__

#include				"Option.hpp"

template				<typename T>
class					OptionValue : public Option
{
public:
  OptionValue<T>(T val) :
  Option(),
    val_(val)
  {}

  virtual ~OptionValue()
  {}

  T const				&getValue() const
  {
    return this->val_;
  }

  void					setValue(T const & val)
  {
    this->val_ = val;
  }
private:
  T					val_;
};

#endif					// __OPTION_VALUE_HH__
