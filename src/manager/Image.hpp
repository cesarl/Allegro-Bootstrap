#ifndef					__IMAGE_HH__
# define				__IMAGE_HH__

#include				<allegro5/allegro.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"

class					Image : public Resource
{
public:
  Image(ALLEGRO_BITMAP *bmp, std::string const & name) :
    Resource(name),
    bmp_(bmp)
  {};

  void					draw() const
  {
    if (this->bmp_)
      al_draw_bitmap(this->bmp_, 40, 40, 0);
  }

  virtual ~Image()
  {
    al_destroy_bitmap(this->bmp_);
  };
private:
  ALLEGRO_BITMAP			*bmp_;
};

typedef					SmartPtr<Image, InternalRef> ImagePtr;

#endif					// __IMAGE_HH__
