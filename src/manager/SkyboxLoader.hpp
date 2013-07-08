#ifndef					__SKYBOX_LOADER_HH__
# define				__SKYBOX_LOADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<map>
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

    ALLEGRO_FS_ENTRY			*fs;
    ALLEGRO_FS_ENTRY			*content;
    ALLEGRO_BITMAP			**bmps = new ALLEGRO_BITMAP*[6];
    int					fileCnt = 0;
    GLuint				cube_map_texture_ID;
    GLenum				cube_map_target[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z
    };
    std::map<std::string, ALLEGRO_LOCKED_REGION*> texture_image;

    fs = al_create_fs_entry(file.getFullName().c_str());
    if (!fs)
      {
	throw LoadingFailed(file.getFullName(), "SkyboxLoader failed to find or open skybox folder.");
      }
    if (!al_open_directory(fs))
      {
	throw LoadingFailed(file.getFullName(), "SkyboxLoader failed to open skybox folder.");
      }
    if (!al_fs_entry_exists(fs))
      {
	throw LoadingFailed(file.getFullName(), "SkyboxLoader can't find folder.");
      }

    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

    while ((content = al_read_directory(fs)))
      {
	const char *name = al_get_fs_entry_name(content);
	ALLEGRO_LOCKED_REGION *r;
	std::cout << name << std::endl;
	bmps[fileCnt] = al_load_bitmap(name);
	if (!bmps[fileCnt])
	  throw LoadingFailed(name, "SkyboxLoader can't load image.");
	r = al_lock_bitmap(bmps[fileCnt], ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	if (!r)
	  throw LoadingFailed(name, "SkyboxLoader can't lock bitmap.");
	texture_image.insert(std::pair<std::string, ALLEGRO_LOCKED_REGION*>(std::string(name), r));
	al_destroy_fs_entry(content);
	++fileCnt;
      }

    al_destroy_fs_entry(fs);

    al_set_new_bitmap_flags(~ALLEGRO_MEMORY_BITMAP);

    // Génération d'une texture CubeMap
    glGenTextures(1, &cube_map_texture_ID);

    if (cube_map_texture_ID == 0)
      throw LoadingFailed(file.getFullName(), "SkyboxLoader error generating a texture.");

    // Configuration de la texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture_ID);

    std::map<std::string, ALLEGRO_LOCKED_REGION*>::iterator it = texture_image.begin();
    int i = 0;
    while (it != texture_image.end())
      {
	glTexImage2D(cube_map_target[i], 0, it->second->pixel_size,
		     al_get_bitmap_width(bmps[i]),
		     al_get_bitmap_height(bmps[i]),
		     0, GL_BGRA, GL_UNSIGNED_BYTE,
		     it->second->data);
	al_unlock_bitmap(bmps[i]);
	++i;
	++it;
      }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);

    return new Skybox(cube_map_texture_ID, bmps, file.getFileName(), force);
  }

  virtual void				save(const Skybox *, const std::string &name)
  {
    throw LoadingFailed(name, "SkyboxLoader doesn't support SAVE.");
  }
};

#endif					// __SKYBOX_LOADER_HH__
