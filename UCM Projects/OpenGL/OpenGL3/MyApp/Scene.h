//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <gtc/matrix_transform.hpp> 
#include <vector>
#include "Camera.h"
#include "Entities.h"
#include "Light.h"
#include"SpotLight.h"
#include "Material.h"
#include "IndexMesh.h"



//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene(Camera* cam): camera(cam) { };
	  ~Scene();
    void init();
	  void render();   

	  void update(GLuint timeElapsed);


	  Diablo* giveDiablo();
	  DiabloText* giveDiabloText();
	  Foto* getFoto();

	  //--------------------------nos devuelven los punteros que nos permiten encender y apagar las luces--------------------------//
	  Light* getLight();
	  Light* getFocalLight();
	  EsferaDeLuz* getEsferaDeLuz();




private:
	  Camera* camera;
	  std::vector<Entity*> objetos;
	  Diablo* d;

	  Foto* foto;
	  DiabloText* dt;


	  bool pictureTaked;
	  GLint xPort;
	  GLint yPort;


	  SpotLight* focalLight_;
	  Light* directionalLight_;


	  Textures textureEsferaDeLuz_;
	  Textures textureVenus_;
	  Textures textureMoon_;
	  Textures textureSun_;
	  Textures textureMars_;
	  Textures textureEatrh_;

	  dmat4 aMatVenus_;
	  dmat4 aMatMars_;
	  dmat4 aMatMoon_;
	  dmat4 aMatSun_;
	  dmat4 aMatTerrain_;

	  Material oroMaterial_;
	  Material silverMaterial_;
	  Material chromeMaterial_;

	  Terreno* terrain_;

	  Esfera* mars_;
	  Esfera* venus_;
	  Esfera* moon_;
	  EsferaDeLuz* sun_;


};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

