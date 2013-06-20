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
    position_(Vector3d(0.0f, 0.0f, -100.0f)),
    rotation_(Vector3d(0.0f, 0.0f, 0.0f)),
    ortho_(Vector3d(0, -1, 0))
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
    return true;
  }

  void					update(float, const ALLEGRO_EVENT &)
  {
    static float a = 0.0f;
    if (a >= 360.0f)
      a = 0.0f;
    glMatrixMode(GL_MODELVIEW),
      glLoadIdentity();

    glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(a, 0.0f, 1.0f, 0.0f); // Y axis, _ang_y variable used here.
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
    a+=1;
  }

  void					updateEnd()
  {
    // glPopMatrix();
  }

  void					input(float time, const ALLEGRO_EVENT &ev)
  {
    // ALLEGRO_MOUSE_STATE			state;
    // Vector3d				pos;

    // al_get_mouse_state(&state);
    // pos = Vector3d(state.x, state.y, 0);
    // pos -= this->center_;
    // pos /= 100.0;
    // std::cout << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;
    // this->direction_ = pos;
    (void)time;
    (void)ev;
  }
private:
  Vector3d				direction_;
  Vector3d				position_;
  Vector3d				rotation_;
  Vector3d				ortho_;
  Vector3d				center_;
};

#endif					// __CAMMERA_HPP__
