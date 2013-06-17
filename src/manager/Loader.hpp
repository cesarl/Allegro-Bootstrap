#ifndef					__LOADER_HPP__
# define				__LOADER_HPP__

#include				"Exception.hh"
#include				"File.hpp"

template				<class T>
class					Loader
{
public:
  virtual				~Loader() {};
  virtual T				*load(const File &file)
  {
    throw LoadingFailed(file.getFullName(), "This loader doesn't support LOAD for this file type.");
  }
  virtual void				save(const T *, const std::string &name)
  {
    throw LoadingFailed(name, "This loader doesn't support SAVE for this file type.");
  }
protected:
  Loader()
  {}
};

// class					ImageLoader : public Loader<ALLEGRO_BITMAP>
// {
// public:
//   virtual				~ImageLoader()
//   {}

//   virtual ALLEGRO_BITMAP		*load(const std::string &name)
//   {
//     ALLEGRO_BITMAP			*bmp;

//     bmp = al_load_bitmap(name.c_str());
//     if (!bmp)
//       throw LoadingFailed(name, "ImageLoader failed to load image.");
//     return bmp;
//   }
//   virtual void				save(const ALLEGRO_BITMAP *, const std::string &name)
//   {
//     throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
//   }
// protected:
//   ImageLoader()
//   {}
// };

#endif					// __LOADER_HPP__
