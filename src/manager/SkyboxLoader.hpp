#ifndef					__SKYBOX_LOADER_HH__
# define				__SKYBOX_LOADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"Image.hpp"
#include				"Skybox.hpp"

class					SkyboxLoader : public Loader<Skybox>
{
public:
  virtual ~SkyboxLoader()
  {}
  virtual Skybox			*load(const File &file, bool force = false)
  {

    //
    // A terminer
    // http://raptor.developpez.com/tutorial/opengl/skybox/

    ALLEGRO_FS_ENTRY *fs;

    fs = al_create_fs_entry(file.getFullName().c_str());
    if (!fs)
      {
	throw LoadingFailed(file.getFullName(), "SkyboxLoader failed to find or open skybox folder.");
      }
    if (!al_open_directory(fs))
      {
	throw LoadingFailed(file.getFullName(), "SkyboxLoader failed to open skybox folder.");
      }



//     // Chargement des six textures
//     AUX_RGBImageRec * texture_image[6];
//     texture_image[0] = LoadBMP( "Skybox/XN.bmp" );
//     texture_image[1] = LoadBMP( "Skybox/XP.bmp" );
//     texture_image[2] = LoadBMP( "Skybox/YN.bmp" );
//     texture_image[3] = LoadBMP( "Skybox/YP.bmp" );
//     texture_image[4] = LoadBMP( "Skybox/ZN.bmp" );
//     texture_image[5] = LoadBMP( "Skybox/ZP.bmp" );

//     // Génération d'une texture CubeMap
//     GLuint cube_map_texture_ID;
//     glGenTextures(1, &cube_map_texture_ID);

//     // Configuration de la texture
//     glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

//     for (int i = 0; i < 6; i++)
//       {
// 	glTexImage2D(cube_map_target[i], 0, 3, texture_image[i]->sizeX, texture_image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image[i]->data);

// 	if (texture_image[i])
// 	  {
// 	    if (texture_image[i]->data)
// 	      {
// 		free(texture_image[i]->data);
// 	      }
// 	    free(texture_image[i]);
// 	  }
//       }

//     glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
// glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);



    ALLEGRO_BITMAP			*bmp;
    GLuint				tex;

    bmp = al_load_bitmap(file.getFullName().c_str());
    if (!bmp)
      throw LoadingFailed(file.getFullName(), "SkyboxLoader failed to load image.");
    tex = al_get_opengl_texture(bmp);
    if (tex == 0)
      throw LoadingFailed(file.getFullName(), "SkyboxLoader failed to load texture.");
    return new Skybox(bmp, tex, file.getFileName(), force);
  }

  virtual void				save(const Skybox *, const std::string &name)
  {
    throw LoadingFailed(name, "SkyboxLoader doesn't support SAVE.");
  }
};

#endif					// __SKYBOX_LOADER_HH__
