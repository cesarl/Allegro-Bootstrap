#ifndef					__IMAGE_LOADER_HH__
# define				__IMAGE_LOADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"Image.hpp"

class					ImageLoader : public Loader<Image>
{
public:
  virtual ~ImageLoader()
  {}
  virtual Image				*load(const File &file, bool force = false)
  {
    ALLEGRO_BITMAP			*bmp;
    GLuint				tex;

    bmp = al_load_bitmap(file.getFullName().c_str());
    if (!bmp)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load image.");
    tex = al_get_opengl_texture(bmp);
    if (tex == 0)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load texture.");
    return new Image(bmp, tex, file.getFileName(), force);
  }
  virtual void				save(const Image *, const std::string &name)
  {
    throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
  }
};

#endif					// __IMAGE_LOADER_HH__
