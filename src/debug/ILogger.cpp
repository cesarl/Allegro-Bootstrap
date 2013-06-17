#include				"ILogger.hh"
#include				"Logger.hpp"

ILogger* ILogger::currentLogger_ = NULL;

ILogger::~ILogger()
{}

void					ILogger::setLogger(ILogger *logger)
{
  if (currentLogger_)
    delete currentLogger_;
  currentLogger_ = logger;
}

void					ILogger::log(const char* format, ...)
{
  //todo compile time expection if !this->currentLogger_
  char					buf[512];
  va_list				params;

  va_start(params, format);
  vsprintf(buf, format, params);
  va_end(params);

  if (!currentLogger_)
    {
      setLogger(new ConsoleLogger);
    }
  currentLogger_->write(buf);
}

ILogger					&ILogger::log()
{
  return *(currentLogger_);
}
