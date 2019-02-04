#include "Scene.h"
#include "iostream"
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);
	// textures
	glEnable(GL_TEXTURE_2D);

	// COMANDOS NECESARIOS PARA QUE SE APLIQUEN LAS PROPIEDADES DE LAS TRASNPARENCIAS Y LA PROFUNDIDAD 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	camera->setAZ();

	// lights

	foto = new Foto(200.0, 200.0, 0, 0, 0, 5, 200);
	objetos.push_back(foto);

	objetos.push_back(new RectanguloText(1000.0,1000.0,20,20,0,0 ,0));
	dt = new DiabloText(100.0, 100.0,200,100,0);
	objetos.push_back(dt);
	//objetos.push_back(new DiabloText(100.0, 100.0, 200, 100, 0));

	objetos.push_back(new Cubo(100.0,0.0,50.0,0));
	objetos.push_back(new Grass(150.0, 150.0, 0, 0, -100.0, 75.0, 150.0));
	objetos.push_back(new GlassPot(100.0, -100.0, 50.0, 150.0));


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