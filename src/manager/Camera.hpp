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
    direction_(Vector3d(0.0f, 0.0f, 0.0f)),
    position_(Vector3d(0.0f, 0.0f, -200.0f)),
    rotation_(Vector3d(0.0f, 0.0f, 0.0f)),
    ortho_(Vector3d(0, 1.0f, 0))
  {}

  ~Camera()
  {}

  bool					init()
  {
    ALLEGRO_DISPLAY			*d;

    d = al_get_current_display();
    if (!d)
      return false;
    this->center_ = Vector3d(al_get_display_width(d) / 2, al_get_display_height(d) / 2, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)((this->center_.getX() * 2) / (this->center_.getY() * 2)), 1.0, 1000.0);
    // glOrtho((double)((this->center_.getX() * 2) / (this->center_.getY() * 2)),
    // 	    (double)((this->center_.getX() * 2) / (this->center_.getY() * 2)),
    // 	    (double)((this->center_.getX() * 2) / (this->center_.getY() * 2)),
    // 	    (double)((this->center_.getX() * 2) / (this->center_.getY() * 2)), 1.0, 1000.0);
    return true;
  }

  void					update(float, const ALLEGRO_EVENT &)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

    glRotatef(this->direction_.getX(), 1.0f, 0.0f, 0.0f);
    glRotatef(this->direction_.getY(), 0.0f, 1.0f, 0.0f); // Y axis, _ang_y variable used here.
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);

    // Vector3d forward = freeMove(Vector3d(0.0f, 0.0f, -1.0f));
    // Vector3d up = freeMove(Vector3d(0.0f, 1.0f, 0.0f));

    gluLookAt(this->position_.x, this->position_.y, this->position_.z,
    	      this->direction_.x, this->direction_.y, this->direction_.z,
	      // this->position_.x + forward.x, this->position_.y+forward.y, this->position_.z+forward.z,
	      this->ortho_.x, this->ortho_.y, this->ortho_.z);
    	      // up.x, up.y, up.z);
    // this->position_ += forward;
    // this->rotation_ += up;
    this->position_ += this->direction_ / Vector3d(100.0,100.0,100.0);
  }

  void					updateEnd()
  {
    // glPopMatrix();
  }

  void					input(float time, const ALLEGRO_EVENT &ev)
  {
    ALLEGRO_MOUSE_STATE			state;
    Vector3d				pos;

    al_get_mouse_state(&state);
    pos = Vector3d(state.x, state.y, 0);
    pos -= this->center_;
    this->direction_ = freeMove(Vector3d((pos.getY() / this->center_.getY()) * 180, (pos.getX() / this->center_.getX()) * 180, 0.0f));
    std::cout << (pos.getX() / this->center_.getX()) * 180 << " " << (pos.getY() / this->center_.getY()) * 180 << std::endl;
    (void)time;
    (void)ev;
  }
private:
   const Vector3d			freeMove(const Vector3d & v)
  {
    if (v.x == 0 && v.y == 0 && v.z == 0)
      return v;
    double rx = this->direction_.x * M_PI / 180;
    double ry = this->direction_.y * M_PI / 180;

    float x = (float)(v.x * cos(ry) + v.y * sin(rx) * sin(ry) - v.z * cos(rx) * sin(ry));
    float y = (float)(v.y * cos(rx) + v.z * sin(rx));
    float z = (float)(v.x * sin(ry) - v.y * sin(rx) * cos(ry) - v.z * cos(rx) * cos(ry));
    return Vector3d(x, y, z);
  }
private:
  Vector3d				direction_;
  Vector3d				position_;
  Vector3d				rotation_;
  Vector3d				ortho_;
  Vector3d				center_;
};

#endif					// __CAMMERA_HPP__
