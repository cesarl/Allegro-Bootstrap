#undef					new
#undef					delete

#include				"MemoryManager.hpp"

bool					MemoryManager::initialize()
{
  return true;
}

void					MemoryManager::deinitialize()
{}

void					*MemoryManager::Allocate(std::size_t size,
								 const char *file,
								 unsigned int line,
								 bool array)
{
  void					*pointer = malloc(size);
  MemBlock				blk;

  if (!pointer)
    return NULL;
  blk.size = size;
  blk.file = file;
  blk.line = line;
  blk.array = array;
  this->blocks_[pointer] = blk;

  this->file_ << "++ A    | 0x"
	      << pointer
	      << " | "
	      << std::setw(7)
	      << std::setfill(' ')
	      << size
	      << " oct"
	      << " | "
	      << file
	      << " : l."
	      << line
	      << std::endl;
  return pointer;
}

void					MemoryManager::Free(void *ptr, bool array)
{
  std::map<void*, MemBlock>::iterator	it;

  it = this->blocks_.find(ptr);

  if (it == this->blocks_.end())
    {
      free(ptr);
      return;
    }

  if (it->second.array != array)
    {
      throw BadDelete(ptr, it->second.file, it->second.line, !array);
    }

  this->file_ << "-- D    | 0x"
	      << ptr
	      << " | "
	      << std::setw(7)
	      << std::setfill(' ')
	      << it->second.size
	      << " oct"
	      << " | "
	      << it->second.file
	      << " : l."
	      << it->second.line
	      << std::endl;
  this->blocks_.erase(it);
  this->nextDelete_.pop();
  free(ptr);
}

void					MemoryManager::nextDelete(const char * file, unsigned int line)
{
  std::cout << "B" << std::endl;
  this->nextDelete_.push(std::pair<const char *, unsigned int>(file, line));
  (void)file; (void)line;
}

MemoryManager::MemoryManager() : file_("memory.log", std::ofstream::out)
{
  std::cout << "A" << std::endl;
}

MemoryManager::~MemoryManager()
{
  std::map<void*, MemBlock>::iterator	it;
  std::size_t				size = 0;

  this->file_ << "END : " << this->blocks_.size() << " leaks detected." << std::endl;
  it = this->blocks_.begin();
  while (it != this->blocks_.end())
    {
      size += it->second.size;
      this->file_ << "-> 0x"
		  << it->first
		  << " | "
		  << std::setw(7)
		  << std::setfill(' ')
		  << it->second.size
		  << " oct"
		  << " | " << it->second.file
		  << " : l."
		  << it->second.line
		  << std::endl;

      free(it->first);
      ++it;
    }
  this->file_ << std::endl << std::endl << "---->"
	      << this->blocks_.size() << " leaks -- "
	      << size << " oct"
	      << std::endl;
  this->blocks_.clear();
}
