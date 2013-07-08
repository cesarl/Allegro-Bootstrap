#include				<iostream>
#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"SkyboxLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"Camera.hpp"
#include				<exception>
#include				<allegro5/allegro_image.h>

static ImagePtr img2;

static Camera<Orthographic, FreeFlight> camera;

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  static SkyboxPtr sky = ResourceManager::getInstance().get<Skybox>("lake.skybox");

  camera.update(time, ev);
  sky->draw(camera.getRotation());
  img2->draw3d();

  (void)ev;
  (void)time;
}

void					key(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);
  (void)time;
}

int					main()
{

  ////////////////////
  // initialisation //
  ////////////////////

  if (!MainManager::getInstance().init())
    return 0;
  if (!MainManager::getInstance().launch(1000, 800))
    return 0;

  //////////
  // main //
  //////////

  /////////////////////////
  // media manager tests //
  /////////////////////////

  try
    {
      MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
      MediaManager::getInstance().registerLoader(new SkyboxLoader, ".skybox");

      MediaManager::getInstance().addSearchPath("./assets/imgs/");

      {
	ImagePtr img = ResourceManager::getInstance().get<Image>("stars.png");
	ImagePtr img1 = ResourceManager::getInstance().get<Image>("stars.png");
	ImagePtr img2 = ResourceManager::getInstance().get<Image>("stars.png");
	ImagePtr img3 = ResourceManager::getInstance().get<Image>("stars.png");
	ILogger::log("Il y a %i instances de la meme image stars.png", img->getCounter());
	img->draw();
	al_flip_display();
      }
      ImagePtr img = ResourceManager::getInstance().get<Image>("stars.png");

      ILogger::log("Il y a %i instances de la meme image stars.png", img->getCounter());
      img->draw();
      al_flip_display();
      MediaManager::getInstance().clearSearchPath();
      MediaManager::getInstance().addSearchPath("./assets/img2/");
      ResourceManager::getInstance().reload<Image>();
      EventManager::getInstance().setDrawLoop(draw);
      EventManager::getInstance().setKeyLoop(key);
      img2 = ResourceManager::getInstance().get<Image>("stars.png");

      if (!camera.init())
	return 0;
      EventManager::getInstance().play();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}




















