#include				<iostream>
#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				<exception>
#include				<allegro5/allegro_image.h>

int					main()
{

  ////////////////////
  // initialisation //
  ////////////////////

  al_init();
  al_init_image_addon();
  al_create_display(300, 300);

  ILogger::setLogger(new ConsoleLogger);

  //////////
  // main //
  //////////

  /////////////////////////
  // media manager tests //
  /////////////////////////

  try
    {
      MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");

      MediaManager::getInstance().addSearchPath("./assets/imgs/");

      // MediaManager::getInstance().load<Image>("stars.png");

      {
	ImagePtr img = ResourceManager::getInstance().get<Image>("stars.png");
	ImagePtr img1 = ResourceManager::getInstance().get<Image>("stars.png");
	ImagePtr img2 = ResourceManager::getInstance().get<Image>("stars.png");
	ImagePtr img3 = ResourceManager::getInstance().get<Image>("stars.png");
	ILogger::log("Il y a %i instances de la meme image stars.png", img->getCounter());
	img->draw();
      }

      ImagePtr img = ResourceManager::getInstance().get<Image>("stars.png");

      ILogger::log("Il y a %i instances de la meme image stars.png", img->getCounter());

      ResourceManager::getInstance().reload();

      al_flip_display();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}
