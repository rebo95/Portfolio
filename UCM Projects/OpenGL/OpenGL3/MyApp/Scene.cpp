#include "Scene.h"
#include "iostream"
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic settin1

	glClearColor(0.005, 0.11, 0.51, 1.0);  // background color (alpha=1 -> opaque)

	glEnable(GL_DEPTH_TEST);
	// textures
	glEnable(GL_TEXTURE_2D);

	// COMANDOS NECESARIOS PARA QUE SE APLIQUEN LAS PROPIEDADES DE LAS TRASNPARENCIAS Y LA PROFUNDIDAD 
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	camera->setAZ();

	//--------------------------------------------------------------- lights-----------------------------------------------------------------//

	directionalLight_ = new Light();
	directionalLight_->setDir(glm::fvec3(0.0, 1.0, 1.0));

	//luz posicional, la hacemos posicional con setPos
	focalLight_ = new SpotLight();
	focalLight_->setAlpha(10.0);
	focalLight_->setPos(camera->giveCameraPosition());
	focalLight_->setFocalDirection(camera->giveCameraFront().x, camera->giveCameraFront().y, camera->giveCameraFront().z);
	//--------------------------------------------------------------------------------------------------------------------------------//



	//foto = new Foto(200.0, 200.0, 0, 0, 0, 5, 200);
	//objetos.push_back(foto);

	/*objetos.push_back(new RectanguloText(1000.0,1000.0,20,20,0,0 ,0));*/
	//dt = new DiabloText(100.0, 100.0,200,100,0);
	//objetos.push_back(dt);
	//objetos.push_back(new DiabloText(100.0, 100.0, 200, 100, 0));

	//objetos.push_back(new Cubo(100.0,0.0,50.0,0));
	//objetos.push_back(new Grass(150.0, 150.0, 0, 0, -100.0, 75.0, 150.0));
	//objetos.push_back(new GlassPot(100.0, -100.0, 50.0, 150.0));


	//---------------------------------------------------carga texturas----------------------------------------------//
	textureMars_.load("..\\Bmps\\mars.bmp");
	textureMoon_.load("..\\Bmps\\moon.bmp");
	textureSun_.load("..\\Bmps\\sun.bmp");
	textureVenus_.load("..\\Bmps\\venus.bmp");
    textureEatrh_.load("..\\Bmps\\BarrenReds.bmp");


	//---------------------------------------------------carga materiales----------------------------------------------//
	oroMaterial_.setGold();
	silverMaterial_.setSilver();
	chromeMaterial_.setChrome();


	dvec3 posIni_;
	

	posIni_ = dvec3(0.0, 0.0, -100.0);
	aMatMars_ = translate(aMatMars_, posIni_);
	mars_ = new Esfera(50.0, 200.0, 100.0);
	mars_->setTexture(textureMars_);
	mars_->setMaterial(chromeMaterial_);
	mars_->setModelMat(aMatMars_);
	objetos.push_back(mars_);

	posIni_ = dvec3(-150.0, 200.0, -500.0);
	aMatVenus_ = translate(aMatVenus_, posIni_);
	venus_ = new Esfera(35.0, 100.0, 100.0);
	venus_->setTexture(textureVenus_);
	venus_->setMaterial(silverMaterial_);
	venus_->setModelMat(aMatVenus_);
	objetos.push_back(venus_);

	posIni_ = dvec3(150.0, 200.0, -70.0);
	aMatMoon_ = translate(aMatMoon_, posIni_);
	moon_ = new Esfera(20.0, 100.0, 100.0);
	moon_->setTexture(textureMoon_);
	moon_->setMaterial(silverMaterial_);
	moon_->setModelMat(aMatMoon_);
	objetos.push_back(moon_);


	//--------------------------------------------------esfera con luz focal y seteado atributos de la pisma-------------------------//
	//--------------------------------------------------hace uso de la clase pointLight----------------------------------------------//

	posIni_ = dvec3(0.0, 20.0, 0.0);
	aMatSun_ = translate(aMatSun_, posIni_);
	sun_ = new EsferaDeLuz(75.0, 100.0, 100.0);
	sun_->setTexture(textureSun_);
	sun_->setMaterial(oroMaterial_);
	sun_->setModelMat(aMatSun_);
	objetos.push_back(sun_);


	//--------------------------------------------------terreno y seteado atributos del terreno-------------------------//
	terrain_ = new Terreno();
	posIni_ = dvec3(0.0, -250.0, 0.0);
	aMatTerrain_ = translate(aMatTerrain_, posIni_);
	terrain_->setTexture(textureEatrh_);
	terrain_->setMaterial(chromeMaterial_);
	terrain_->setModelMat(aMatTerrain_);
	objetos.push_back(terrain_);
	

	//OBTIENE LAS DIMENSIONES DE LA VENTANA
	xPort = camera->getVP()->getW();
	yPort = camera->getVP()->getH();
	
}

//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
  glMatrixMode(GL_MODELVIEW);

  GLint xPort = camera->getVP()->getW();
  GLint yPort = camera->getVP()->getH();
  camera->getVP()->setPosition(0, 0);
  // recordar que hay que cargar las luces para que se rendericen de manera correcta cada vez que entramos en el 

  //---------------------------------------------------Rendelizado, posicionamiento y objetivo del foco------------------------------//
  focalLight_->setPos(camera->giveCameraPosition());
  focalLight_->setFocalDirection(camera->giveCameraFront().x, camera->giveCameraFront().y, camera->giveCameraFront().z);
  focalLight_->load(camera->getViewMat());

  //---------------------------------------------------Rendelizado, posicionamiento y objetivo de la luz direccional------------------------------//
 directionalLight_->load(camera->getViewMat()); 

  for each (Entity* it in objetos)
  {

	  it->render(camera->getViewMat());
  }
	
  //---------------------------------------------------CODIGO QUE NOS PERMITE RENDERIZAR EN PATALLA UNA MATRIZ DE OBJETOS CUADRADA DISTIBUIDOS UNIFOMEMENTE POR LA PANTALLA 
	//GLint numeroPuertosVista,numeroDivisiones,wPuertoDeVista, hPuertoDeVista;
	//numeroPuertosVista = objetos.size();
	//numeroDivisiones = sqrt(numeroPuertosVista); // van a ser siempre matrices cuadradas

	//GLint posx, posy;

	//wPuertoDeVista = xPort / numeroDivisiones;
	//hPuertoDeVista = yPort / numeroDivisiones;

	//GLint p;
	//p = xPort / 6;
	//posx = 0;
	//posy = (numeroDivisiones-1)*hPuertoDeVista;

	//std::vector<Entity*> ::iterator it = objetos.begin();
	//for (int i = 0; i < numeroDivisiones; i++) {
	//	for (int j = 0; j < numeroDivisiones; j++) {

	//		//camera->getVP()->setPosition(-2*p, posy);
	//		camera->getVP()->setPosition(posx, posy);
	//		camera->getVP()->setSize(wPuertoDeVista, hPuertoDeVista);
	//		(*it)->render(camera->getViewMat());
	//		++it;
	//		posx += wPuertoDeVista;
	//	}
	//	posx = 0;
	//	posy -= hPuertoDeVista;
	//}


	//camera->getVP()->setPosition(0, 0);
	//(*it)->render(camera->getViewMat());
	//++it;

	/*camera->getVP()->setPosition(xPort / 4, yPort / 4);
	(*it)->render(camera->getViewMat());
	++it;

	camera->getVP()->setPosition(-xPort / 4, -yPort / 4);
	(*it)->render(camera->getViewMat());
	++it;

	camera->getVP()->setPosition(xPort / 4, -yPort / 4);
	(*it)->render(camera->getViewMat());*/
}
//-------------------------------------------------------------------------



Diablo* Scene::giveDiablo() {
	return d;
}

DiabloText* Scene::giveDiabloText() {
	return dt;
}
//PARA PODER ROTAR EL DIABOLO NECESITAMOS UN PUNTERO AL MISMO , PARA DESDE EL MAIN, PODER LLAMAR A ÉSTE MÉTODO QUE NOS DEVUELVA UN PUNTERO Y PODER LLAMAR A UN MÉTODO DEL OBJETO

Foto* Scene::getFoto() {
	return foto;
}

void Scene::update(GLuint timeElapsed) {
	for each (Entity* it in objetos)
	{
		it->update(timeElapsed);
	}
}


Light* Scene::getLight()
{
	return directionalLight_;
}


Light* Scene::getFocalLight()
{
	return focalLight_;
}


EsferaDeLuz* Scene::getEsferaDeLuz() {
	return sun_;
}