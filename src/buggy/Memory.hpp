#ifndef					__MEMORY_HH__
# define				__MEMORY_HH__

#include				"MemoryManager.hpp"

inline void				*operator new(std::size_t size, const char *file, unsigned int line)
{
  return MemoryManager::getInstance().Allocate(size, file, line, false);
}

inline void				*operator new[](std::size_t size, const char *file, unsigned int line)
{
  return MemoryManager::getInstance().Allocate(size, file, line, true);
}

inline void				operator delete(void *ptr)
{
  MemoryManager::getInstance().Free(ptr, false);
}

inline void				operator delete[](void *ptr)
{
  MemoryManager::getInstance().Free(ptr, true);
}

inline void				operator delete(void *ptr, const char *file, unsigned int line)
{
  MemoryManager::getInstance().nextDelete(file, line);
  MemoryManager::getInstance().Free(ptr, false);
}

inline void				operator delete[](void *ptr, const char *file, unsigned int line)
{
  MemoryManager::getInstance().nextDelete(file, line);
  MemoryManager::getInstance().Free(ptr, true);
}

# ifndef				new
#  define				new new(__FILE__, __LINE__)
# endif

# ifndef				delete
#  define				delete MemoryManager::getInstance().nextDelete(__FILE__, __LINE__), delete
# endif

#endif					// __MEMORY_HH__
