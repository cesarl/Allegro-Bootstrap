#ifndef					__MEMORY_MANAGER_HH__
# define				__MEMORY_MANAGER_HH__

#include				<cstdlib>
#include				<fstream>
#include				<iostream>
#include				<map>
#include				<stack>
#include				<iomanip>
#include				"Exception.hh"
#include				"Singleton.hpp"

struct					MemBlock
{
  std::size_t				size;
  const char				*file;
  unsigned int				line;
  bool					array;
};

class					MemoryManager : public Singleton<MemoryManager>
{
public:
  void					*Allocate(std::size_t size,
						  const char *file,
						  unsigned int line,
						  bool array);
  void					Free(void *ptr, bool array);
  void					nextDelete(const char * file, unsigned int line);
  virtual bool				initialize();
  virtual void				deinitialize();
private:
  MemoryManager();
  ~MemoryManager();
  std::map<void*, MemBlock>		blocks_;
  std::stack<std::pair<const char *, unsigned int> > nextDelete_;
  std::ofstream				file_;
};

#endif					// __MEMORY_MANAGER_HH__
