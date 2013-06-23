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
    speed_(30.0f)
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
    al_set_mouse_xy(d, this->center_.x, this->center_.y);
    al_grab_mouse(d);

    al_get_mouse_state(&state);
    this->focus_ = this->center_;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)((this->center_.getX() * 2.0f) / (this->center_.getY() * 2.0f)), 1.0, 1000.0);
    this->theta_ = 0.0f;
    this->phi_ = 0.0f;
    updateVectors();
    return true;
  }

  void					update(float, const ALLEGRO_EVENT &)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // gluLookAt(this->position_.x, this->position_.y, this->position_.z,
    // 	      this->target_.x, this->target_.y, this->target_.z,
    // 	      0, 1, 1);

    glRotatef(this->phi_, 1.0f, 0.0f, 0.0f);
    glRotatef(this->theta_, 0.0f, 1.0f, 0.0f);
    glTranslatef(-this->position_.x, -this->position_.y, -this->position_.z);

    ALLEGRO_MOUSE_STATE			state;
    Vector3d				pos;

    al_get_mouse_state(&state);
    pos = Vector3d(state.x, state.y, 0.0f);
    this->focus_ -= pos;

    this->theta_ -= (float)this->focus_.x * this->sensitivity_;
    this->phi_ -= (float)this->focus_.y * this->sensitivity_;

    this->focus_ = pos;
    // std::cout << state.x <<  " " << state.y <<std::endl;

    updateVectors();
    std::cout << this->theta_<<  " " << this->phi_ <<std::endl;

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
    if (al_key_down(&k, ALLEGRO_KEY_S))
      {
	this->position_ -= this->forward_ * Vector3d(speed, speed, speed);
      }
    if (al_key_down(&k, ALLEGRO_KEY_A))
      {
	this->position_ += this->left_ * Vector3d(speed, speed, speed);
      }
    if (al_key_down(&k, ALLEGRO_KEY_D))
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

    // this->left_ = Vector3d(cos(this->phi_ * M_PI / 180.0f), sin(this->phi_ * M_PI / 180.0f), 0.0f);
    // this->left_ = this->left_.normal();
    // this->target_ = this->position_ + this->forward_;
    this->left_ = Vector3d(0.0f, 0.0f, 0.0f);
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
