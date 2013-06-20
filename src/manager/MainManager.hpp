#ifndef					__MAIN_MANAGER_HPP__
# define				__MAIN_MANAGER_HPP__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<allegro5/allegro_image.h>
#include				"Singleton.hpp"
#include				"EventManager.hpp"

class					MainManager :
  public				Singleton<MainManager>
{
  friend class				Singleton<MainManager>;
public:
  bool					init()
  {
    if (!al_init())
      return false;
    if (!al_init_image_addon())
      return false;
    ILogger::setLogger(new ConsoleLogger);
al_set_new_bitmap_flags(ALLEGRO_MIPMAP | ALLEGRO_MIN_LINEAR);
    return true;
  }

  bool					launch(int width, int height)
  {
    al_set_new_display_flags(ALLEGRO_OPENGL_3_0);
    if (!al_create_display(width, height))
      return false;
    if (!EventManager::getInstance().init())
      return false;
    return true;
  }
private:
  MainManager(){}
  ~MainManager()
  {
    al_destroy_display(al_get_current_display());
  }
};

#endif					// __MAIN_MANAGER_HPP__
