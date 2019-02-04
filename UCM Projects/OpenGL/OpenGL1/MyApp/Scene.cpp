#include "Scene.h"
#include "iostream"
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);

	camera->setAZ();

	// lights
	// textures  

	// objets
	//objetos.push_back(new EjesRGB(200.0));
	objetos.push_back(new TrianguloRGB(100.0));
	objetos.push_back(new Triangulo(100.0));
	objetos.push_back(new TriPyramid(100.0, 100.0));

	objetos.push_back(new ContCubo(100.0));
	objetos.push_back(new Rectangulo(100.0, 50.0));

	d = new Diablo(100.0, 100.0);
	objetos.push_back(d);
	objetos.push_back(new Cubo(100.0));


	objetos.push_back(new Poliespiral(0.0,0.0,0.0,160.0,50,2, 50));
	objetos.push_back(new Dragon(3000));

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


	//for each (Entity* it in objetos)
	//{
	//	GLint xPort = camera->getVP()->getW();
	//	GLint yPort = camera->getVP()->getH();
	//	camera->getVP()->setPosition(-xPort/4,-yPort/4);
	//	it->render(camera->getViewMat());
	//
	GLint numeroPuertosVista,numeroDivisiones,wPuertoDeVista, hPuertoDeVista;
	numeroPuertosVista = objetos.size();
	numeroDivisiones = sqrt(numeroPuertosVista); // van a ser siempre matrices cuadradas



	GLint posx, posy;



	wPuertoDeVista = xPort / numeroDivisiones;
	hPuertoDeVista = yPort / numeroDivisiones;

	GLint p;
	p = xPort / 6;
	posx = 0;
	posy = (numeroDivisiones-1)*hPuertoDeVista;

	std::vector<Entity*> ::iterator it = objetos.begin();
	for (int i = 0; i < numeroDivisiones; i++) {
		for (int j = 0; j < numeroDivisiones; j++) {

			//camera->getVP()->setPosition(-2*p, posy);
			camera->getVP()->setPosition(posx, posy);
			camera->getVP()->setSize(wPuertoDeVista, hPuertoDeVista);
			(*it)->render(camera->getViewMat());
			++it;
			posx += wPuertoDeVista;
		}
		posx = 0;
		posy -= hPuertoDeVista;
	}


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
