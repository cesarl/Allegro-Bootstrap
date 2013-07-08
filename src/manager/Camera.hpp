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

  virtual ~FreeFlight()
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
    // al_set_mouse_xy(d, center.x, center.y);
    // al_grab_mouse(d);

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
    this->rotation_ = Vector3d(this->phi_, this->theta_, 0.0f);
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
    if (al_key_down(&k, ALLEGRO_KEY_A))
      {
	Vector3d up(0.0f, 1.0f, 0.0f);
	Vector3d left = up.crossProduct(this->forward_);
	this->position_ += left.normal();
      }
    if (al_key_down(&k, ALLEGRO_KEY_D))
      {
	Vector3d up(0.0f, 1.0f, 0.0f);
	Vector3d left = up.crossProduct(this->forward_);
	this->position_ -= left.normal();
      }
    if (al_key_down(&k, ALLEGRO_KEY_Q))
      {
	this->position_ += Vector3d(0.0f, this->speed_ / 20.0f, 0.0f);
      }
    if (al_key_down(&k, ALLEGRO_KEY_E))
      {
	this->position_ -= Vector3d(0.0f, this->speed_ / 20.0f, 0.0f);
      }

    lastTime = time;
    (void)ev;
    (void)time;
  }

  inline const Vector3d			&getPosition() const throw()
  {
    return this->position_;
  }

  inline const Vector3d			&getRotation() const throw()
  {
    return this->rotation_;
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
  Vector3d				rotation_;
};

class					Perspective
{
public:
  explicit Perspective() throw() :
    center_(Vector3d(0.0f, 0.0f, 0.0f))
  {}

  virtual ~Perspective()
  {}

  inline bool				initRender() throw()
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
    return true;
  }

  inline void				updateRender(float, const ALLEGRO_EVENT &) throw()
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  inline void				inputRender(float, const ALLEGRO_EVENT &) throw()
  {}

private:
  Vector3d				center_;
};

class					Orthographic
{
public:
  explicit Orthographic() throw() :
    min_(Vector3d(0.0f, 0.0f, 0.0f)),
    max_(Vector3d(0.0f, 0.0f, 0.0f)),
    size_(Vector3d(0.0f, 0.0f, 0.0f)),
    center_(Vector3d(0.0f, 0.0f, 0.0f))
  {}

  virtual ~Orthographic()
  {}

  inline bool				initRender() throw()
  {
    ALLEGRO_DISPLAY			*d;
    Vector3d				pos;

    d = al_get_current_display();
    if (!d)
      return false;
    this->size_ = Vector3d(al_get_display_width(d), al_get_display_height(d), 0.0f);
    this->center_ = Vector3d(this->size_.x / 2.0f, this->size_.y / 2.0f, 0.0f);
    this->max_ = this->min_;
    this->max_ += this->size_;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(this->min_.x, this->max_.x, this->min_.y, this->max_.y, 1.0, 1000.0);
    return true;
  }

  inline void				updateRender(float, const ALLEGRO_EVENT &) throw()
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  inline void				inputRender(float, const ALLEGRO_EVENT &) throw()
  {}

private:
  Vector3d				min_;
  Vector3d				max_;
  Vector3d				size_;
  Vector3d				center_;
};


template				<class CameraRender, class CameraBehavior>
class					Camera : public CameraRender, public CameraBehavior
{
public:
  Camera()
  {
  }

  virtual ~Camera()
  {}

  bool					init()
  {
    if (!this->initRender())
      return false;
    return this->initBehavior();
  }

  void					update(float time, const ALLEGRO_EVENT &ev)
  {
    this->updateRender(time, ev);
    this->updateBehavior(time, ev);
  }

  void					updateEnd()
  {
  }

  void					input(float time, const ALLEGRO_EVENT &ev)
  {
    this->inputRender(time, ev);
    this->inputBehavior(time, ev);
    (void)ev;
    (void)time;
  }
};

#endif					// __CAMMERA_HPP__



