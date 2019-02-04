

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
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}

Triangulo::Triangulo(GLdouble r) : Entity() {
	mesh = Mesh::generateTriangle(r);
}

TrianguloRGB::TrianguloRGB(GLdouble r) : Entity() {
	mesh = Mesh::generateTriangleRGB(r);
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity() {
	mesh = Mesh::generateRectangle(w, h);
}

TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity() {

	mesh = Mesh::generateTriPyramid(r, h);
}

ContCubo::ContCubo(GLdouble l) {
	mesh = Mesh::generateContCubo(l);
}

Dragon::Dragon(GLuint numVert) {
	mesh = Mesh::generaDragon(numVert);
}

Poliespiral::Poliespiral(GLdouble x, GLdouble y, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {

	mesh = Mesh::generaPoliespiral(x, y,angIni, incrAng,ladoIni,incrLado, numVert);
}

Diablo::Diablo(GLdouble r, GLdouble h) : altura(h) {
	mesh = Mesh::generateTriPyramid(r, h);
}

Cubo::Cubo(GLdouble l): lado(l){
	mesh = Mesh::generateContCubo(l);
	mesh2 = Mesh::generateRectangle(l, l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}

void Triangulo :: draw() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();

}

void TrianguloRGB::draw() {

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	mesh->draw();
}

void Rectangulo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

void TriPyramid:: draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

void ContCubo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

void Dragon::draw() {
	glPointSize(2);
	mesh->draw();
}

void Poliespiral::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}

void Cubo::draw() {
}



/*.........................................................................................*/
//CLASE DRAGON
void Diablo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
}


void Diablo::render(glm::dmat4 const& modelViewMat) {
	//recordemos que h ya estaba en el eje Z
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(angulo), dvec3(0.0, 0.0, 1.0));// dibujamos los objetos a partir de la primera piramide, si rotamos la primera, esto afecta a todo.
	aMat = translate(aMat, dvec3(0.0, 0.0, - altura));

	glLoadMatrixd(value_ptr(aMat));
	Diablo::draw();

	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	Diablo::draw();

	aMat = rotate(aMat, radians(180.0), dvec3(1.0, 0.0, 0.0));
	aMat = translate(aMat, dvec3(0.0, 0.0, -2*altura));
	glLoadMatrixd(value_ptr(aMat));

	Diablo::draw();


	aMat = rotate(aMat, radians(60.0), dvec3(0.0, 0.0, 1.0));
	aMat = translate(aMat, dvec3(0.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	Diablo::draw();
}

Mesh* Diablo::returnMesh() {
	return mesh;
}

void Diablo::rotaDiablo() {
	angulo += 5;
}

void Dragon::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(-40.0, -170.0, 0.0));
	aMat = scale(aMat, dvec3(40.0, 40.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	Dragon::draw();
}
//-------------------------------------------------------------------------
//clase CuboTapa
void Cubo::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);


	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();

	aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(0.0, lado/2 +(lado / 2)*cos(radians(40.0)), -(lado/2-(lado/2)*sin(radians(40.0)))));
	aMat = rotate(aMat, radians(40.0), dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh2->draw();

	aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(0.0, -lado/2, 0.0));
	aMat = rotate(aMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh2->draw();


}