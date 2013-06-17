#ifndef					__MEDIA_MANAGER_HPP__
# define				__MEDIA_MANAGER_HPP__

#include				<map>
#include				<set>
#include				<vector>
#include				<string>
#include				"Typelist.hpp"
#include				"GenHierarchies.hpp"
#include				"SmartPointer.hpp"
#include				"Loader.hpp"
#include				"strUtil.hpp"
#include				"Exception.hh"
#include				"File.hpp"
#include				"Singleton.hpp"
#include				"Image.hpp"

// todo definir la liste des medias pris en charge
typedef					TYPELIST_1(Image) MediaList;

template				<class T>
struct					MediaHolder
{
  typedef				std::map<std::string, SmartPtr<Loader<T> > > LoaderMap;
  LoaderMap				loaders;
};

class					MediaManager :
  public Singleton<MediaManager>,
  public CScatteredHierarchy<MediaList, MediaHolder>
{
  // for constructor and singleton
  friend class Singleton<MediaManager>;

public:
  template				<class T>
  void					load(const File &file) const
  {
    File				path;

    path = this->findMedia(file);
    path.getFileName();
    this->findLoader<T>(path).load(path.getFullName());
  }

  void					addSearchPath(const std::string &path)
  {
    if (path.empty() || (*(path.begin()) == '\\') || (*(path.rbegin()) == '/'))
      {
	this->paths_.insert(path);
      }
    else
      {
	this->paths_.insert(path + "\\");
      }
  }

  template				<class T>
  inline void				registerLoader(Loader<T> *loader, const std::string &extensions)
  {
    std::vector<std::string>		ext;
    SmartPtr<Loader<T> >		ptr;
    std::vector<std::string>::iterator	it;

    split(extensions, ext, " /\\*.,;|-_\t\n'\"");

    ptr = loader;
    it = ext.begin();
    while (it != ext.end())
      {
	// todo toLower
	MediaHolder<T>::loaders[(*it)] = ptr;
	++it;
      }
  }

  template				<class T>
  void					save(const T *object, const File &file) const
  {
    this->findLoader<T>(file).save(object, file.getFullName());
  }

private:
  MediaManager()
  {
    this->paths_.insert("");
  }

  ~MediaManager()
  {}

  File					findMedia(const File &file) const
  {
    std::set<std::string>::const_iterator	it;

    it = this->paths_.begin();
    while (it != this->paths_.end())
      {
	File				f;

	f = *it + file.getFileName();
	if (f.exists())
	  return f;
	++it;
      }
    throw LoadingFailed(file.getFullName(), "File cannot be found.");
  }

  template				<class T>
  inline Loader<T>			&findLoader(const File &file) const
  {
   typename  MediaHolder<T>::LoaderMap::const_iterator	it;

    // todo tolower
    it = MediaHolder<T>::loaders.find(file.getExtension());
    if (it != MediaHolder<T>::loaders.end() && it->second)
      {
	return *(it->second);
      }
    throw LoadingFailed(file.getFullName(), "No loader handle this type of file.");
  }

private:
  std::set<std::string>			paths_;
};

#endif					// __MEDIA_MANAGER_HPP__
