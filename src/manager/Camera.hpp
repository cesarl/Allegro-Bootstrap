#ifndef					__CAMERA_HPP__
# define				__CAMERA_HPP__

#include                                <allegro5/allegro.h>
#include				<GL/glu.h>
#include				<cmath>
#include				"Vector3d.hh"

class					Camera
{
public:
  Camera() :
    target_(Vector3d(0.0f, 0.0f, 0.0f)),
    position_(Vector3d(0.0f, 0.0f, 200.0f)),
    forward_(Vector3d(0.0f, 0.0f, 0.0f)),
    focus_(Vector3d(0.0f, 0.0f, 0.0f)),
    center_(Vector3d(0.0f, 0.0f, 0.0f)),
    left_(Vector3d(0.0f, 0.0f, 0.0f)),
    theta_(0.0f),
    phi_(0.0f),
    sensitivity_(1.0f),
    speed_(10.0f)
  {
    this->updateVectors();
  }

  ~Camera()
  {}

  bool					init()
  {
    ALLEGRO_DISPLAY			*d;
    ALLEGRO_MOUSE_STATE			state;
    Vector3d				pos;

    d = al_get_current_display();
    if (!d)
      return false;
    this->center_ = Vector3d(al_get_display_width(d) / 2.0f, al_get_display_height(d) / 2.0f, 0.0f);

    al_get_mouse_state(&state);
    this->focus_ = Vector3d(state.y, state.x, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)((this->center_.getX() * 2.0f) / (this->center_.getY() * 2.0f)), 1.0, 1000.0);
    return true;
  }

  void					update(float, const ALLEGRO_EVENT &)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(this->position_.x, this->position_.y, this->position_.z,
	      this->target_.x, this->target_.y, this->target_.z,
	      0, 1, 0);

    ALLEGRO_MOUSE_STATE			state;
    Vector3d				pos;

    // glPushMatrix();
    // glLoadIdentity();
    al_get_mouse_state(&state);
    pos = Vector3d(state.x, state.y, 0.0f);
    // glPopMatrix();

    pos -= this->center_;
    pos /= this->center_;
    this->theta_ -= (float)pos.x * this->sensitivity_;
    this->phi_ -= (float)pos.y * this->sensitivity_;

    std::cout << state.x <<  " " << state.y <<std::endl;

    // std::cout << this->theta_<<  " " << this->phi_ <<std::endl;
    updateVectors();

  }

  void					updateEnd()
  {
    // glPopMatrix();
  }

  void					input(float time, const ALLEGRO_EVENT &ev)
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
    else if (al_key_down(&k, ALLEGRO_KEY_S))
      {
	this->position_ -= this->forward_ * Vector3d(speed, speed, speed);
      }
    if (al_key_down(&k, ALLEGRO_KEY_A))
      {
	this->position_ += this->left_ * Vector3d(speed, speed, speed);
      }
    else if (al_key_down(&k, ALLEGRO_KEY_D))
      {
	this->position_ -= this->left_ * Vector3d(speed, speed, speed);
      }

    // case ALLEGRO_KEY_S:
    //   break;
    // case ALLEGRO_KEY_A:
    //   break;
    // case ALLEGRO_KEY_D:
    //   break;
    // }

    lastTime = time;
    (void)ev;
    (void)time;
  }
private:
  void					updateVectors()
  {
    static	Vector3d		up(0.0f, 1.0f, 1.0f);

    if (this->phi_ > 89.0)
      {
	this->phi_ = 89.0;
      }
    else if (this->phi_ < -89.0)
      {
	this->phi_ = -89.0;
      }

    double				r;

    r = cos(this->phi_ * M_PI / 180);
    this->forward_.z = sin(this->phi_ * M_PI / 180);
    this->forward_.x = r * cos(this->theta_ * M_PI / 180);
    this->forward_.y = r * sin(this->theta_ * M_PI / 180);

    this->left_ = up.crossProduct(this->forward_);
    this->left_.normal();
    this->target_ = this->position_ + this->forward_;
    // std::cout << this->target_.x << " " << this->target_.y << " " << this->target_.x << std::endl;
  }
private:
  Vector3d				target_;
  Vector3d				position_;
  Vector3d				forward_;
  Vector3d				focus_;
  Vector3d				center_;
  Vector3d				left_;
  double				theta_;
  double				phi_;
  float					sensitivity_;
  float					speed_;
};

#endif					// __CAMMERA_HPP__
