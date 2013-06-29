#ifndef					__SKYBOX_HPP__
# define				__SKYBOX_HPP__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Vector3d.hh"
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"

class					Skybox : public Resource
{
public:
  Skybox(ALLEGRO_BITMAP *bmp, GLuint tex, std::string const & name, bool force) :
    Resource(name, force),
    bmp_(bmp),
    tex_(tex)
  {};

  virtual void				operator=(Skybox & o)
  {
    if (this->bmp_)
      al_destroy_bitmap(this->bmp_);
    this->bmp_ = o.bmp_;
    this->tex_ = o.tex_;
  }

  void					draw(const Vector3d & position, const Vector3d & size) const
  {
    glPushMatrix();

    glTranslatef(position.x,position.y,position.z);

    glScalef(size.x,size.y,size.z);

    float r = 1.0f; // If you have border issues change this to 1.005f

    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor4f(1.0, 1.0, 1.0, 1.0f);

    glBindTexture(GL_TEXTURE_2D, this->tex_);

    // Common Axis Z - FRONT Side
    glBegin(GL_QUADS);
    glTexCoord2f(0.25f, 0.3333333f); glVertex3f(-r, 1.0f, -r);
    glTexCoord2f(0.25f, 0.6666666f); glVertex3f(-r, 1.0f, r);
    glTexCoord2f(0.0f, 0.6666666f); glVertex3f( r,1.0f, r);
    glTexCoord2f(0.0f, 0.3333333f); glVertex3f( r,1.0f,-r);
    glEnd();

    // Common Axis Z - BACK side
    glBegin(GL_QUADS);
    glTexCoord2f(0.75f, 0.3333333f);  glVertex3f(-r,-1.0f,-r);
    glTexCoord2f(0.75f, 0.6666666f);  glVertex3f(-r,-1.0f, r);
    glTexCoord2f(0.50f, 0.6666666f);  glVertex3f( r,-1.0f, r);
    glTexCoord2f(0.50f, 0.3333333f);  glVertex3f( r,-1.0f,-r);
    glEnd();

    // Common Axis X - Left side
    glBegin(GL_QUADS);
    glTexCoord2f(0.5f, 0.6666666f); glVertex3f(-1.0f, -r, r);
    glTexCoord2f(0.25f, 0.6666666f); glVertex3f(-1.0f,  r, r);
    glTexCoord2f(0.25f, 0.3333333f); glVertex3f(-1.0f,  r,-r);
    glTexCoord2f(0.5f, 0.3333333f); glVertex3f(-1.0f, -r,-r);
    glEnd();

    // Common Axis X - Right side
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.6666666f); glVertex3f(1.0f, -r, r);
    glTexCoord2f(0.75f, 0.6666666f); glVertex3f(1.0f,  r, r);
    glTexCoord2f(0.75f, 0.3333333f); glVertex3f(1.0f,  r,-r);
    glTexCoord2f(1.0f, 0.3333333f); glVertex3f(1.0f, -r,-r);
    glEnd();

    // Common Axis Y - Draw Up side
    glBegin(GL_QUADS);
    glTexCoord2f(0.25f, 0.0f); glVertex3f( r, -r, 1.0f);
    glTexCoord2f(0.50f, 0.0f); glVertex3f( r,  r, 1.0f);
    glTexCoord2f(0.50f, 0.3333333f); glVertex3f(-r,  r, 1.0f);
    glTexCoord2f(0.25f, 0.3333333f); glVertex3f(-r, -r, 1.0f);
    glEnd();

    // Common Axis Y - Down side
    glBegin(GL_QUADS);
    glTexCoord2f(0.25f, 0.6666666f); glVertex3f( r, -r, -1.0f);
    glTexCoord2f(0.50f, 0.6666666f); glVertex3f( r,  r, -1.0f);
    glTexCoord2f(0.50f, 1.0f); glVertex3f(-r,  r, -1.0f);
    glTexCoord2f(0.25f, 1.0f); glVertex3f(-r, -r, -1.0f);
    glEnd();

    // Load Saved Matrix
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  virtual ~Skybox()
  {
    if (this->bmp_)
      al_destroy_bitmap(this->bmp_);
  };
private:
  ALLEGRO_BITMAP			*bmp_;
  GLuint				tex_;
};

typedef					SmartPtr<Skybox, InternalRef> SkyboxPtr;

#endif					// __SKYBOX_HPP__
