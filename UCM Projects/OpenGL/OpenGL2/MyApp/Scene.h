//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "Camera.h"
#include "Entities.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene(Camera* cam): camera(cam) { };
	  ~Scene();
    void init();
	  void render();    
	  Diablo* giveDiablo();
	  DiabloText* giveDiabloText();
	  Foto* getFoto();
	  void update(GLuint timeElapsed);

protected:
	  Camera* camera;
	  std::vector<Entity*> objetos;
	  Diablo* d;

	  Foto* foto;
	  DiabloText* dt;

	  bool pictureTaked;
	  GLint xPort;
	  GLint yPort;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

