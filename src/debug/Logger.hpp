#ifndef					__LOGGER_HPP__
# define				__LOGGER_HPP__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_native_dialog.h>
#include				<fstream>
#include				"ILogger.hh"
#include				"Exception.hh"

class					ConsoleLogger : public ILogger
{
private:
  virtual void				write(const std::string & message)
  {
    std::clog << message << std::endl;
  }
};

class					DebugLogger : public ILogger
{
public:
  DebugLogger(std::string const & title = "Debug window")
  {
    this->window_ = al_open_native_text_log(title.c_str(),
					    ALLEGRO_TEXTLOG_NO_CLOSE
					    | ALLEGRO_TEXTLOG_MONOSPACE);
  }
  virtual ~DebugLogger()
  {
    al_close_native_text_log(this->window_);
  }
private:
  virtual void				write(const std::string & message)
  {
    al_append_native_text_log(this->window_, message.c_str());
  }
  ALLEGRO_TEXTLOG			*window_;
};

//////////////////////////////////
// todo : don't write to file ! //
// I don't know why !	        //
// To fix		        //
//////////////////////////////////

class					FileLogger : public ILogger
{
public:
  FileLogger(const std::string & name = "out.log") : file_(name.c_str(), std::ofstream::app | std::ofstream::out)
  {
    if (this->file_.fail())
      throw LoadingFailed("out.log", "std::ofstream opening failed");
  }
  virtual ~FileLogger()
  {
    this->file_.close();
  }
private:
  virtual void				write(const std::string & message)
  {
    this->file_ << message;
  }
  std::ofstream				file_;
};

#endif					// __LOGGER_HPP__
