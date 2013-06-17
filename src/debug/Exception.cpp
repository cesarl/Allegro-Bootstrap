#include				"Exception.hh"

Exception::Exception(const std::string &message) throw() :
  message_(message)
{}

Exception::~Exception() throw()
{}

const char				*Exception::what() const throw()
{
  return this->message_.c_str();
}

AssertException::AssertException(const std::string &file, unsigned int line, const std::string &message)
{
  std::ostringstream			f;

  f << message << std::endl << std::endl;
  f << file << " l." << line << std::endl;
  this->message_ = f.str();
}

BadDelete::BadDelete(const void *ptr, const std::string &file, unsigned int line, bool newArray)
{
  std::ostringstream			f;

  f << "Problem "
     << (newArray ? "new " : "delete ")
     << std::endl << std::endl
     << "Adr : 0x" << ptr << std::endl
     << "File : " << file << " l. " << line << std::endl;
  this->message_ = f.str();
}

LoadingFailed::LoadingFailed(const std::string &file, const std::string &message)
{
  std::ostringstream			f;

  f << "Loading error of file " << file << std::endl << std::endl << message << std::endl;
  this->message_ = f.str();
}

OutOfMemory::OutOfMemory(const std::string & message) :
  Exception(message)
{}
