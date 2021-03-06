#ifndef					__IMAGE_HH__
# define				__IMAGE_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"

class					Image : public Resource
{
public:
  Image(ALLEGRO_BITMAP *bmp, GLuint tex, std::string const & name, bool force) :
    Resource(name, force),
    bmp_(bmp),
    tex_(tex)
  {};

  void					draw() const
  {
    if (this->bmp_)
      al_draw_bitmap(this->bmp_, 40, 40, 0);
  }

  virtual void				operator=(Image & o)
  {
    if (this->bmp_)
      al_destroy_bitmap(this->bmp_);
    this->bmp_ = o.bmp_;
    this->tex_ = o.tex_;
  }

  void					draw3d() const
  {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, this->tex_);
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTranslatef(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);

    glColor3f(1.0f,1.0f,1.0f);
    glTexCoord2f(0.0, 0.0); // Top left hand corner
    glVertex3f(0.0, 0.0, 0.0); // X,Y,Z
    glTexCoord2f(1.0, 0.0); // Bottom left hand corner
    glVertex3f(100.0, 0.0, 0.0); // X,Y,Z
    glTexCoord2f(1.0, 1.0); // Bottom right hand corner
    glVertex3f(100.0, 100.0, 0.0); // X,Y,Z
    glTexCoord2f(0.0, 1.0); // Top right hand corner
    glVertex3f(0, 100.0, 0.0); // X,Y,Z

    glEnd();

    glScalef(20.0f, 20.0f, 20.0f);

    glBegin(GL_TRIANGLES);
    //Triangle 1
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    //Triangle 2
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    //Triangle 3
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
    //Triangle 4
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }

  virtual ~Image()
  {
    if (this->bmp_)
      al_destroy_bitmap(this->bmp_);
    glDeleteTextures(1, &tex_);
  };
private:
  ALLEGRO_BITMAP			*bmp_;
  GLuint				tex_;
};

typedef					SmartPtr<Image, InternalRef> ImagePtr;

#endif					// __IMAGE_HH__
