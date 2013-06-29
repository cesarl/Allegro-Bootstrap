#ifndef					__CAMERA_HPP__
# define				__CAMERA_HPP__

#include                                <allegro5/allegro.h>
#include				<GL/glu.h>
#include				<cmath>
#include				"Vector3d.hh"

class					FreeFlight
{
public:
  explicit				FreeFlight() throw() :
    position_(Vector3d(0.0f, 0.0f, 200.0f)),
    forward_(Vector3d(0.0f, 0.0f, 0.0f)),
    focus_(Vector3d(0.0f, 0.0f, 0.0f)),
    theta_(0.0f),
    phi_(0.0f),
    sensitivity_(1.0f),
    speed_(30.0f)
  {}

  inline bool				initBehavior() throw()
  {
    ALLEGRO_DISPLAY			*d;
    Vector3d				pos;
    Vector3d				center;

    d = al_get_current_display();
    if (!d)
      return false;
    center = Vector3d(al_get_display_width(d) / 2.0f, al_get_display_height(d) / 2.0f, 0.0f);
    al_set_mouse_xy(d, center.x, center.y);
    al_grab_mouse(d);

    this->focus_ = center;

    this->theta_ = 0.0f;
    this->phi_ = 0.0f;
    this->updateVectors();
    return true;
  }

  inline void				updateBehavior(float, const ALLEGRO_EVENT &) throw()

  {
    ALLEGRO_MOUSE_STATE			state;
    Vector3d				pos;

    al_get_mouse_state(&state);
    pos = Vector3d(state.x, state.y, 0.0f);
    this->focus_ -= pos;

    this->theta_ -= (float)this->focus_.x * this->sensitivity_;
    this->phi_ -= (float)this->focus_.y * this->sensitivity_;

    this->focus_ = pos;

    this->updateVectors();

    glRotatef(this->phi_, 1.0f, 0.0f, 0.0f);
    glRotatef(this->theta_, 0.0f, 1.0f, 0.0f);
    glTranslatef(-this->position_.x, -this->position_.y, -this->position_.z);
  }

  inline void				inputBehavior(float time, const ALLEGRO_EVENT &ev)
  {
    static float			lastTime = -1;
    ALLEGRO_KEYBOARD_STATE		k;

    al_get_keyboard_state(&k);

    if (lastTime == -1)
      lastTime = al_get_time();
    float speed = (time - lastTime) * this->speed_;

    if (al_key_down(&k, ALLEGRO_KEY_W))
      {
	this->position_ += this->forward_ * Vector3d(speed, speed, speed);
      }
    if (al_key_down(&k, ALLEGRO_KEY_S))
      {
	this->position_ -= this->forward_ * Vector3d(speed, speed, speed);
      }

    lastTime = time;
    (void)ev;
    (void)time;
  }

  inline const Vector3d			&getPosition() const throw()
  {
    return this->position_;
  }

private:
  void					updateVectors()
  {
    if (this->phi_ > 89.0)
      {
	this->phi_ = 89.0;
      }
    else if (this->phi_ < -89.0)
      {
	this->phi_ = -89.0;
      }

    if (this->theta_ > 360.0)
      {
	this->theta_ = 0.0;
      }
    else if (this->theta_ < 0.0)
      {
	this->theta_ = 360.0;
      }

    double				r;

    r = cos(this->phi_ * M_PI / 180.0f);
    this->forward_.x = r * sin(this->theta_ * M_PI / 180.0f);
    this->forward_.y = sin(this->phi_ * M_PI / 180.0f * -1.0f);
    this->forward_.z = r * cos(this->theta_ * M_PI / 180.0f) * -1.0f * cos(this->phi_ * M_PI / 180.0f);
  }
private:
  Vector3d				position_;
  Vector3d				forward_;
  Vector3d				focus_;
  double				theta_;
  double				phi_;
  float					sensitivity_;
  float					speed_;
};

template				<class CameraBehavior>
class					Camera : public CameraBehavior
{
public:
  Camera() :
    center_(Vector3d(0.0f, 0.0f, 0.0f))
  {
  }

  ~Camera()
  {}

  bool					init()
  {
    ALLEGRO_DISPLAY			*d;
    Vector3d				pos;

    d = al_get_current_display();
    if (!d)
      return false;
    this->center_ = Vector3d(al_get_display_width(d) / 2.0f, al_get_display_height(d) / 2.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)((this->center_.getX() * 2.0f) / (this->center_.getY() * 2.0f)), 1.0, 1000.0);
    return this->initBehavior();
  }

  void					update(float time, const ALLEGRO_EVENT &ev)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    this->updateBehavior(time, ev);
  }

  void					updateEnd()
  {
  }

  void					input(float time, const ALLEGRO_EVENT &ev)
  {
    this->inputBehavior(time, ev);
    (void)ev;
    (void)time;
  }
private:
  Vector3d				center_;
};

#endif					// __CAMMERA_HPP__



