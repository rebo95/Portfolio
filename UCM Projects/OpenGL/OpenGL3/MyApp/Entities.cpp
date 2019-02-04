

#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

}

void Entity::setModelMat(glm::dmat4 const& mMat) {
	modelMat = mMat;
}

void Entity::setMaterial(Material const& mt) {
	material = mt;
}

void Entity::setTexture(Textures const& tex) {
	texture = tex;
}

//---------------------------------------------------------------------------------
//--------------------------------RGB AXES-----------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}

void EjesRGB::draw()
{
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}


//---------------------------------------------------------------------------------
//--------------------------------TRIANGULO-----------------------------------------

Triangulo::Triangulo(GLdouble r) : Entity() {
	mesh = Mesh::generateTriangle(r);
}

void Triangulo::draw() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();

}
//-------------------------------------------------------------------------------------------------------------------------
//--------------------------------TRIANGULORGB---------------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble r) : Entity() {
	mesh = Mesh::generateTriangleRGB(r);
}

void TrianguloRGB::draw() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}
//-------------------------------------------------------------------------------------------------------------------------
//--------------------------------RECTANGULO---------------------------------------------------------------------------------

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity() {
	mesh = Mesh::generateRectangle(w, h);

}

void Rectangulo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mesh->draw();
}

//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------RECTANGULO TEXTURIZADO---------------------------------------------------------------------------------


RectanguloText::RectanguloText(GLdouble w, GLdouble h, int repeticiones_patron_x, int repeticiones_patron_y, int posX, int posY, int posZ) : Entity(), iniX(posX), iniY(posY), iniZ(posZ) {
	mesh = Mesh::generateRectangleText(w, h, repeticiones_patron_x, repeticiones_patron_y);
	texture.load("..\\Bmps\\baldosaC.bmp");
}

void RectanguloText::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind(GL_REPLACE);
	mesh->draw();
	texture.unbind();
}

void RectanguloText::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;// EN EL CASO DE VOLVER A LLAMARLO REINICIAMOS LA MATRIZ ORIGINAL A SUS POSICIONES ORIGINALES
	aMat = translate(aMat, dvec3(iniX, iniY, iniZ));
	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));

	glLoadMatrixd(value_ptr(aMat)); //DEBEMOS LANZAR ESTE MÉTODO SIEMPRE ANTES DEL DRAW PARA QUE LA MANTRIZ ACTUAL DESPUÉS DE LAS TRANSFORMACIONES SE CARGUE Y SE PUEDA PINTAR
	draw();
}

//------------------------------------------------------------------------------------------------------------
//--------------------------------FOTO(HEREDA DE RECTANGULOTEXTURIZADO-----------------------------------------


Foto::Foto(GLdouble w, GLdouble h, int x, int y, int posX, int posY, int posZ) : RectanguloText(w, h, x, y, posX, posY, posZ) {
	texture.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------PIRAMIDE NO TEXTURIZADA--------------------------------------------------------------------------------------------------------
TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity() {
	mesh = Mesh::generateTriPyramid(r, h);
}

void TriPyramid::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------PIRAMIDE TEXTURIZADA--------------------------------------------------------------------------------------------------------
//utiliza el mesh de la tripirámide

TriPyramidText::TriPyramidText(GLdouble r, GLdouble h):Entity()
{
	mesh = Mesh::generateTriPyramidText(r, h);
	texture.load("..\\Bmps\\Zelda.bmp");
};

void TriPyramidText::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind(GL_REPLACE);
	mesh->draw();
	texture.unbind();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO NO TEXTURIZADO--------------------------------------------------------------------------------------------------------


ContCubo::ContCubo(GLdouble l) {
	mesh = Mesh::generateContCubo(l);
}

void ContCubo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO TEXTURIZADO--------------------------------------------------------------------------------------------------------
//utiliza el mesh del cubo no texturizado


CuboText::CuboText(GLdouble l) {
	mesh = Mesh::generateCubeText(l);// para generar un elmento con textura necesitamos un nuevo generador de malla, pero ALLI usamos la malla del obgeto que le da forma
	texture.load("..\\Bmps\\container.bmp");
	texture2.load("..\\Bmps\\chuches.bmp");
}

void CuboText::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//texture1.load("..\\Bmps\\container.bmp");
	glEnable(GL_CULL_FACE); //NECESARIO PARA QUE NOS RENDERICE LA TEXTURA SOLO EN LA CARA QUE NOSOTROS DESEAMOS 
	glCullFace(GL_FRONT);

	texture.bind(GL_REPLACE);
	mesh->draw();
	texture.unbind();

	glCullFace(GL_BACK);
	//texture2.load("..\\Bmps\\chuches.bmp");
	texture2.bind(GL_REPLACE);
	mesh->draw();
	texture2.unbind();
	glDisable(GL_CULL_FACE);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------DRAGON (POINT GENERATED)------------------------------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) {
	mesh = Mesh::generaDragon(numVert);
}

void Dragon::draw() {
	glPointSize(2);
	mesh->draw();
}

//trasnformaciones finales a la clase dragón , se hacen desde su método render (redefinido)
void Dragon::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(-40.0, -170.0, 0.0));
	aMat = scale(aMat, dvec3(40.0, 40.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	Dragon::draw();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------POLIESPIRAL-----------------------------------------------------------------------------------------------------------

Poliespiral::Poliespiral(GLdouble x, GLdouble y, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {

	mesh = Mesh::generaPoliespiral(x, y,angIni, incrAng,ladoIni,incrLado, numVert);
}

void Poliespiral::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------DIABOLO NO TEXTURIZADO------------------------------------------------------------------------------------------------

Diablo::Diablo(GLdouble r, GLdouble h) : altura(h) {
	mesh = Mesh::generateTriPyramid(r, h); // diablo no necesita una malla nueva, pues usa la de la pirámide para hacer su composición desde su (diablo),
	//render
}

void Diablo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

void Diablo::render(glm::dmat4 const& modelViewMat) {
	//recordemos que h ya estaba en el eje Z
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat; // MUY IMPORTANTE INICIAR LA VARIABLE MATRIZ CON LA QUE VAMOS A TRABAJAR LAS TRANSFORMACIONES

	aMat = rotate(aMat, radians(angulo), dvec3(0.0, 0.0, 1.0));// dibujamos los objetos a partir de la primera piramide, si rotamos la primera, esto afecta a todo.
	aMat = translate(aMat, dvec3(0.0, 0.0, -altura));

	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(180.0), dvec3(1.0, 0.0, 0.0));
	aMat = translate(aMat, dvec3(0.0, 0.0, -2 * altura));
	glLoadMatrixd(value_ptr(aMat));

	draw();


	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	aMat = translate(aMat, dvec3(0.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
	// EN ESTE CASO VAMOS HACIENDO TRANSFORMACIONES SONBRE LA TRANSFORMADA, VAMOS ANIDADNO TRANSFORMACIONES, SIEMPRE , TRANSFORMAMOS Y PINTAMOS 
}

Mesh* Diablo::returnMesh() {
	return mesh;
}


void Diablo::rotaDiablo() {
	angulo += 5;
}


void Diablo::update(GLuint timeElapsed) {
	angulo = mod(angulo + speed * timeElapsed, 360.0);
}



//----------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------DIABOLO TEXTURIZADO------------------------------------------------------------------------------------------------


DiabloText::DiabloText(GLdouble r, GLdouble h, int x, int y, int z) : altura(h), iniX(x), iniY(y), iniZ(z) {
	mesh = Mesh::generateTriPyramidText(r, h);
	texture.load("..\\Bmps\\floris.bmp");
	//ocurre lo mismo en este caso, pero ahora necesitamos la malla del triángulo texturizado, que al generar su mesh, toma el mesh de la piramide 
}

void DiabloText::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->draw();
}

void DiabloText::render(glm::dmat4 const& modelViewMat) {
	//recordemos que h ya estaba en el eje Z
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(iniX, iniY, iniZ));

	texture.bind(GL_REPLACE);

	aMat = rotate(aMat, radians(angulo), dvec3(0.0, 0.0, 1.0));// dibujamos los objetos a partir de la primera piramide, si rotamos la primera, esto afecta a todo.
	aMat = translate(aMat, dvec3(0.0, 0.0, -altura));

	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(180.0), dvec3(1.0, 0.0, 0.0));
	aMat = translate(aMat, dvec3(0.0, 0.0, -2 * altura));
	glLoadMatrixd(value_ptr(aMat));

	draw();


	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	aMat = translate(aMat, dvec3(0.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
	texture.unbind();
}

Mesh* DiabloText::returnMesh() {
	return mesh;
}

void DiabloText::rotaDiabloText() {
	//angulo += 5;
	angulo = mod(angulo + 5, 360.0);
}

void DiabloText::update(GLuint timeElapsed) {
	angulo = mod(angulo + speed * timeElapsed, 360.0);
}



//----------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO_TAPA_RELLENO_TEXTURA2------------------------------------------------------------------------------------------
//utiliza el mesh del cubotext y rectangletext

Cubo::Cubo(GLdouble l, int x, int y, int z): lado(l), iniX(x), iniY(y), iniZ(z){
	mesh = Mesh::generateCubeText(l);
	mesh2 = Mesh::generateRectangleText(l, l,0,0);
	texture.load("..\\Bmps\\container.bmp");
	texture2.load("..\\Bmps\\chuches.bmp");
}

void Cubo::draw() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	texture.bind(GL_REPLACE);
	mesh->draw();
	texture.unbind();

	glCullFace(GL_BACK);

	texture2.bind(GL_REPLACE);
	mesh->draw();
	texture2.unbind();
	glDisable(GL_CULL_FACE);
}

void Cubo::draw2() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.bind(GL_REPLACE);
	mesh2->draw();
	texture.unbind();
}


void Cubo::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(iniX, iniY, iniZ));
	dmat4 aMatIni = aMat;

	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = aMatIni;

	aMat = translate(aMat, dvec3(0.0, lado / 2 + (lado / 2)*cos(radians(40.0)), -(lado / 2 - (lado / 2)*sin(radians(40.0)))));
	aMat = rotate(aMat, radians(40.0), dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw2();

	aMat = aMatIni;
	aMat = translate(aMat, dvec3(0.0, -lado / 2, 0.0));
	aMat = rotate(aMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw2();
}



//-----------------------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO DE CRISTAL-----------------------------------------------------------------------------

GlassPot::GlassPot(GLdouble l, int x, int y, int z): lado(l), iniX(x), iniY(y), iniZ(z) {
	mesh = Mesh::generateCubeText(l);
	texture.load("..\\Bmps\\window.bmp", 150);
}

void GlassPot::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthMask(GL_FALSE); // COMANDO NECESARIO PARA QUE SE APLIQUEN LAS FUNCIONES DEL BUFFER DE PROFUNDIDAD Y POR TANTO LAS TRANSPARENCIAS 
	texture.bind(GL_REPLACE);
	mesh->draw();
	texture.unbind();
	glDepthMask(GL_TRUE);
}
void GlassPot::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(iniX, iniY, iniZ));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}


//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------HIERBA--------------------------------------------------------------------------------------------


Grass::Grass(GLdouble w, GLdouble h, int x, int y, int posX, int posY, int posZ): iniX(posX), iniY(posY), iniZ(posZ) {
	mesh = Mesh::generateRectangleText(w, h, x,y);
	ivec3 color = {0.0, 0.0, 0.0};
	texture.load("..\\Bmps\\grass.bmp", color, 0);
	texture.wrap();
}

void Grass::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthMask(GL_FALSE);
	texture.bind(GL_REPLACE);
	mesh->draw();
	texture.unbind();
	glDepthMask(GL_TRUE);
}

void Grass::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(iniX, iniY, iniZ));
	aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
	aMat = rotate(aMat, radians(90.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------FOTO ( HEREDA DE LA CLASE RECTANGLE TEXT)------------------------------------------------------------------------
// la clase foto no necesita redefinir los métodos de draw y render pues son heredados diréctamente de la clase rectangulo texturizado
void Foto::update(GLuint timeElapsed) {

	tempo += timeElapsed;
	if (tempo > 1500) {
		texture.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		tempo = 0;
	}
}
void Foto::getPicture() {
	texture.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------ESFERA--------------------------------------------------------------------------------------------

Esfera::Esfera(GLdouble radio, GLdouble meridianos, GLdouble paralelos) : paralelos_(paralelos), meridianos_(meridianos), radio_(radio){
	qObj = gluNewQuadric();
}
Esfera:: ~Esfera() {
	gluDeleteQuadric(qObj);
}

void Esfera::render(glm::dmat4 const& modelViewMat) {

	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

	draw();
}
void Esfera::draw() {

	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricNormals(qObj, GLU_SMOOTH);
	/*	gluQuadricOrientation(qObj, GLU_OUTSIDE);*/ //recordemos que siempre es el render el que llama al draw() por cada vuelta del bucle
	gluQuadricTexture(qObj, GL_TRUE);

	texture.bind(GL_MODULATE);
	material.load();
	gluSphere(qObj, radio_, meridianos_, paralelos_);
	texture.unbind();
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------ESFERADELUZ--------------------------------------------------------------------------------------------
EsferaDeLuz::EsferaDeLuz(GLdouble radio, GLdouble meridianos, GLdouble paralelos):  Esfera(radio,meridianos, paralelos)
{
	foco = new SpotLight();

	foco->setPos(dvec3(0.0, 0.0, 0.0));
	foco->setAlpha(20.0);
	foco->setFocalDirection(0.0, -1.0, 0.0);

	//generamos los elementod hijos y los hijos de los hijos de la clase padre
	esfera1 = new Esfera(radio/3, meridianos, paralelos);
	esfera2 = new Esfera(radio /3, meridianos, paralelos);


	//establecemos los atributos e los elementos hijos y los hijos de los hijos
	esfera1->setModelMat(modelMat);
	esfera2->setModelMat(modelMat);

	texture2.load("..\\Bmps\\moon.bmp");
	esfera1->setTexture(texture2);
	esfera2->setTexture(texture2);

	materialEsfera1.setChrome();
	materialEsfera2.setChrome();

	esfera1->setMaterial(materialEsfera1);
	esfera2->setMaterial(materialEsfera2);
}

void EsferaDeLuz::render(glm::dmat4 const& modelViewMat) {

	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	//transformaciones de la trayectoria y movimiento del objeto padre en función de su matriz de modelado
	aMat = translate(aMat, trayectoria);
	aMat = rotate(aMat, radians(angulo), dvec3(0.0, 1.0, 0.0));

	glLoadMatrixd(value_ptr(aMat));

	foco->load(aMat);

	draw();
	renderEsfera1(aMat);
	renderEsfera2(aMat);
}

void EsferaDeLuz::renderEsfera1(glm::dmat4 const& modelViewMat) {
	
	//generamos las esferas haciendo las transformaciones con respecto a la matriz de modelado de la clase padre, esto es , hacer que su aMat = modelViewMat * esfera1->giveModelMat();
	// siendo la matriz de modelado de cada una de las esferas inicializada a la matriz de la esfera padre.

	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * esfera1->giveModelMat();
	aMat = translate(aMat, glm::dvec3(radio_ + radio_/3  , 0.0,0.0));
	glLoadMatrixd(value_ptr(aMat));
	esfera1->draw();
}

void EsferaDeLuz::renderEsfera2(glm::dmat4 const& modelViewMat) {

	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * esfera2->giveModelMat();
	aMat = translate(aMat, glm::dvec3(-radio_ - radio_ /3, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	esfera2->draw();
}


void EsferaDeLuz::update(GLuint timeElapsed) {

	//modifica los atributso que determinan la trayectoria del objeto
	trayectoria = dvec3(Cx * cos(radians(angulo)), Cy * sin(radians(angulo)) * sin(radians(angulo)), Cz * sin(radians(angulo)) * cos(radians(angulo)));
	angulo = mod(angulo + speed * timeElapsed, 360.0);
}

SpotLight* EsferaDeLuz :: giveLight() {
	//nos permitira activar y desactivar las luces si llamamos a este métdodo desde otros métodos como el main, siempre y cuando desde alli se nos
	//facilite un puntero al objeto de esta clase
	return foco;
}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------Terreno--------------------------------------------------------------------------------------------

Terreno::Terreno() {
	imesh = IndexMesh::generateTerrain();
}

void Terreno::render(glm::dmat4 const& modelViewMat) {
	
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

void Terreno::draw() {
	texture.bind(GL_MODULATE);
	material.load();
	imesh->draw();
	texture.unbind();
}