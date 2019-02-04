#include "Material.h"



Material::Material()
{
	ambient = { 0.1, 0.1, 0.1, 1 };
	diffuse = { 0.5, 0.5, 0.5, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
}


Material::~Material()
{
}

void Material::load() {
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
}

//debemos realizar seters que doten de características especiales a los materiales, con estos seters estamos dando a cada material las propiedades relectoras 
// del material en cuestión. Debemos jugar con los valores de las variables ambient , diffuse , specular 
void Material::setGold() {
	ambient = { 0.24725, 0.1995, 0.0745, 1 };
	diffuse = { 0.75164, 0.60648, 0.22648, 1 };
	specular = { 0.628281, 0.555802, 0.366065, 1 };
	expF = 51.2;
}
void Material::setSilver() {

	ambient = { 0.192525, 0.192525,0.192525, 1 };
	diffuse = { 0.50754, 0.50754, 0.50754, 1 };
	specular = { 0.508273, 0.508273, 0.508273, 1 };
	expF = 51.2;
}
void Material::setChrome() {
	ambient = { 0.25, 0.25, 0.25, 1.0 };
	diffuse = { 0.4, 0.4, 0.4, 1.0 };
	specular = { 0.774597, 0.774597, 0.774597, 1.0 };
	expF = 76.8;
}