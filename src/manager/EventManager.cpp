#include				"EventManager.hh"

EventManager::EventManager() :
  event_queue_(NULL),
  timer_(NULL),
  sceneManager_(NULL)
{
}

EventManager::~EventManager()
{
}

bool					EventManager::initialize()
{
}

void					EventManager::uninitialize()
{
  if (this->event_queue_)
    al_destroy_event_queue(this->event_queue_);
  if (this->timer_)
    al_destroy_timer(this->timer_);
  al_uninstall_keyboard();
  al_uninstall_mouse();
}


void					EventManager::play()
{
}

void					EventManager::stop()
{
  this->run_->setValue(false);
}

EventManager				*EventManager::getInstance()
{
  static EventManager			that;
  return &that;
}
