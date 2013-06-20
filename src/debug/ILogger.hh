#ifndef					__ILOGGER_HH__
# define				__ILOGGER_HH__

#include				<string>
#include				<iostream>
#include				<cstdarg>
#include				<cstdio>

#undef					new
#undef					delete

class					ILogger
{
public:
  virtual				~ILogger();
  static void				setLogger(ILogger *logger);
  static void				log(const char *format, ...);
  static ILogger			&log();
  static void				log(const std::string & s);

  template				<class T>
  ILogger				&operator<<(const T &toLog);
private:
  virtual void				write(const std::string &message) = 0;
  static ILogger			*currentLogger_;
};

#endif					// __ILOGGER_HH__
