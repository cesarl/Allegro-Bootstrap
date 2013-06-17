#ifndef					__IMAGE_LOADER_HH__
# define				__IMAGE_LOADER_HH__

#include				<allegro5/allegro.h>
#include				"Loader.hpp"
#include				"Image.hpp"

class					ImageLoader : public Loader<Image>
{
public:
  virtual ~ImageLoader()
  {}
  virtual Image				*load(const File &file)
  {
    ALLEGRO_BITMAP			*bmp;

    bmp = al_load_bitmap(file.getFullName().c_str());
    if (!bmp)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load image.");
    return new Image(bmp, file.getFileName());
  }
  virtual void				save(const Image *, const std::string &name)
  {
    throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
  }
};

#endif					// __IMAGE_LOADER_HH__
