#ifndef					__EXCEPTION_HH__
# define				__EXCEPTION_HH__

#include				<sstream>

class					Exception : public::std::exception
{
public:
  Exception(const std::string & message = "") throw();
  virtual ~Exception() throw();
  virtual const char *what() const throw();
protected:
  std::string				message_;
};

struct AssertException : public Exception
{
  AssertException(const std::string &file, unsigned int line, const std::string & message);
};

struct BadDelete : public Exception
{
  BadDelete(const void *ptr, const std::string &file, unsigned int line, bool newArray);
};

struct LoadingFailed : public Exception
{
  LoadingFailed(const std::string &file, const std::string &message);
};

struct OutOfMemory : public Exception
{
  OutOfMemory(const std::string &message);
};

# ifdef					_DEBUG
#  define				Assert(condition) if (!(condition)) \
    throw AssertException(__FILE__, __LINE__, "Unsatisfied condition\n\n" #condition)
#else
inline void DoNothing(bool){}
#  define				Assert(condition) DoNothing(!(condition))
# endif

#endif					// __EXCEPTION_HH__
