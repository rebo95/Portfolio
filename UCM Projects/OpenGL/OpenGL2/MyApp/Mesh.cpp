#include "Mesh.h"
#include <gtc/constants.hpp>
using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
  delete[] texCoords;
}
//-------------------------------------------------------------------------

void Mesh::draw() {
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
    }
	if (texCoords != nullptr) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY); // LAS COORDENADAS FUNCIONAN GRACIAS A HABER HABILITADO ESTA INSTRUCCION 
		glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	}
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//---------------------------------------------------------------------------------
//--------------------------------RGB AXES-----------------------------------------
Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-----------------------------------------------------------------------------------------
//--------------------------------TRIANGULO PLANO -----------------------------------------
Mesh * Mesh::generateTriangle(GLdouble r) {
	Mesh* t = new Mesh();
	t->type = GL_TRIANGLES;
	t->numVertices = 3;

	//x = Cx + R cos ang
	//y = Cy + R sin ang
	
	t->vertices = new dvec3[t->numVertices];
	t->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	t->vertices[1] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0.0);
	t->vertices[2] = dvec3(r*cos(radians(320.0)), r*sin(radians(330.0)), 0.0);

	t->colors = new dvec4[t->numVertices];
	t->colors[0] = dvec4(0.0,0.0,0.0, 1.0);
	t->colors[1] = dvec4(0.0, 0.0, 0.0, 1.0);
	t->colors[2] = dvec4(0.0, 0.0, 0.0, 1.0);// cada una de las esquinas de la texura se le asocia a un vértice de la figura que estamos creando 

	return t;

}
//-----------------------------------------------------------------------------------------
//--------------------------------TRIANGULO PLANO RGB -----------------------------------------
Mesh * Mesh::generateTriangleRGB(GLdouble r) {
	Mesh* tRGB = new Mesh();
	tRGB->type = GL_TRIANGLES;
	tRGB->numVertices = 3;

	tRGB->vertices = new dvec3[tRGB->numVertices];
	tRGB->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	tRGB->vertices[1] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0.0);
	tRGB->vertices[2] = dvec3(r*cos(radians(330.0)), r*sin(radians(330.0)), 0.0);

	tRGB->colors = new dvec4[tRGB->numVertices];
	tRGB->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	tRGB->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	tRGB->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return tRGB;

}
//-----------------------------------------------------------------------------------------
//--------------------------------PIRAMIDE TRIANGULAR DE LADO BASE R Y ALTURA H -----------------------------------------
Mesh* Mesh::generateTriPyramid(GLdouble r, GLdouble h) {
	Mesh* p = new Mesh();
	p->type = GL_TRIANGLE_FAN;
	p->numVertices = 5;

	p->vertices = new dvec3[p->numVertices];
	p->vertices[0] = dvec3(0.0, 0.0, h);/* dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);*/
	p->vertices[1] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0.0);
	p->vertices[2] = dvec3(r*cos(radians(330.0)), r*sin(radians(330.0)), 0.0);
	p->vertices[3] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	p->vertices[4] = p->vertices[1];

	p->colors = new dvec4[p->numVertices];
	p->colors[0] = dvec4(0.0, 0.0, 0.0, 1.0);
	p->colors[1] = dvec4(0.0, 0.0, 0.0, 1.0);
	p->colors[2] = dvec4(0.0, 0.0, 0.0, 1.0);

	return p;
}

//-----------------------------------------------------------------------------------------
//--------------------------------PIRAMIDE TRIANGULAR TEXTURIZADA -----------------------------------------
Mesh* Mesh::generateTriPyramidText(GLdouble r, GLdouble h) {

	Mesh* TPT = generateTriPyramid(r, h);//UTILIZAMOS LA MALLA DEL OBJETO SIN TEXTURIZAR 
	TPT->texCoords = new dvec2[TPT->numVertices];

	TPT->texCoords[0] = dvec2(0.5, 1);
	TPT->texCoords[1] = dvec2(0, 1);
	TPT->texCoords[2] = dvec2(0, 0);
	TPT->texCoords[3] = dvec2(1, 0);
	TPT->texCoords[4] = dvec2(1, 1);

	return TPT;
}

//-----------------------------------------------------------------------------------------
//--------------------------------GENERA FIGURA CUBO-----------------------------------------
Mesh* Mesh:: generateContCubo(GLdouble l) {
	Mesh* c = new Mesh();
	c->type = GL_TRIANGLE_STRIP;
	c->numVertices = 10;

	c->vertices = new dvec3[c->numVertices];
	c->vertices[0] = dvec3(-l / 2, -l/2, l / 2);
	c->vertices[1] = dvec3(-l / 2, l / 2, l / 2);
	c->vertices[2] = dvec3(l/2, -l / 2, l/2);
	c->vertices[3] = dvec3(l / 2, l / 2, l / 2);
	c->vertices[4] = dvec3(l / 2, -l / 2, -l / 2);
	c->vertices[5] = dvec3(l / 2, l / 2, -l / 2);
	c->vertices[6] = dvec3(-l / 2, -l / 2, -l / 2);
	c->vertices[7] = dvec3(-l / 2, l / 2, -l / 2);
	c->vertices[8] = dvec3(-l / 2, -l / 2, l / 2);
	c->vertices[9] = dvec3(-l / 2, l / 2, l / 2);

	c->colors = new dvec4[c->numVertices];
	c->colors[0] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[1] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[2] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[3] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[4] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[5] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[6] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[7] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[8] = dvec4(0.0, 0.0, 0.0, 1.0);
	c->colors[9] = dvec4(0.0, 0.0, 0.0, 1.0);

	return c;
}

//-----------------------------------------------------------------------------------------
//--------------------------------GENERA CUBO TEXTURIZADO-----------------------------------------
Mesh* Mesh ::generateCubeText(GLdouble l){

	Mesh* cT = generateContCubo(l);

	cT->texCoords = new dvec2[cT->numVertices];
	cT->texCoords[0] = dvec2(0, 0);
	cT->texCoords[1] = dvec2(1, 0);
	cT->texCoords[2] = dvec2(0, 1);
	cT->texCoords[3] = dvec2(1, 1);

	cT->texCoords[4] = dvec2(0, 0);
	cT->texCoords[5] = dvec2(1, 0);
	cT->texCoords[6] = dvec2(0, 1);
	cT->texCoords[7] = dvec2(1, 1);

	cT->texCoords[8] = dvec2(0, 0);
	cT->texCoords[9] = dvec2(1, 0);

	return cT;
}


//-----------------------------------------------------------------------------------------
//--------------------------------GENERA DRAGON HACIENDO USO DE PUNTOS-----------------------------------------
Mesh* Mesh::generaDragon(GLuint numVert){
	// comenzamos en el vertice 0,0 estamos dibujamdo puntos
	// la transfomacion que vamos a aplicar aquí es la rotación 

	double PR1 = 0.787473;
	double azar;

	Mesh* dragon = new Mesh();
	dragon->type = GL_POINTS;
	dragon->numVertices = numVert;


	dragon->vertices = new dvec3[dragon->numVertices];
	dragon->colors = new dvec4[dragon->numVertices];
	dragon->vertices[0] = dvec3(0.0,0.0,0.0);//el primer vértice está en 0,0
	dragon->colors[0] = dvec4(0.0, 0.0, 1.0, 1.0);

	//ahora es donde entramos en el bucle y vamos aplicando las transformaciones correspondientes.
	for (int i = 1; i < dragon->numVertices; i++) {
		azar = rand() / double(RAND_MAX); // MANERA DE OBTENER UN NÚMERO ALEATORIO 

		if (azar<PR1)
			dragon->vertices[i] = dvec3((0.824074 * dragon->vertices[i - 1].x + 0.281482 * dragon->vertices[i - 1].y - 0.882290),( -0.212346 * dragon->vertices[i - 1].x + 0.864198 * dragon->vertices[i - 1].y - 0.110607), 0.0);
		else
			dragon->vertices[i] = dvec3((0.088272 * dragon->vertices[i - 1].x + 0.520988 * dragon->vertices[i - 1].y + 0.785360),(-0.463889 * dragon->vertices[i - 1].x - 0.377778 * dragon->vertices[i - 1].y + 8.095795), 0.0);

		dragon->colors[i] = dvec4(0.0,0.0,1.0, 1.0);
	}
	//debemos ir pintando todos los puntos aplicando la traslación correspondiente al punto anterior.
	// el primer punto 
	return dragon;

}

//-----------------------------------------------------------------------------------------
//--------------------------------GENERA POLIESPIRAL MEDIANTE LA COMBINACION DE LÍNEAS -----------------------------------------
Mesh* Mesh:: generaPoliespiral(GLdouble x, GLdouble y, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {
	const double PI = glm::pi<double>();
	Mesh* pE = new Mesh(); 
	pE->type = GL_LINE_STRIP;
	pE->numVertices = numVert;


	pE->vertices = new dvec3[pE->numVertices];
	pE->colors = new dvec4[pE->numVertices];

	pE->vertices[0] = dvec3(x, y, 0.0);
	pE->colors[0] = dvec4(0.0, 1.0, 0.0, 1.0);
	pE->vertices[1] = dvec3(pE->vertices[0].x + ladoIni * cos(radians(angIni)), pE->vertices[0].y + ladoIni * sin(radians(angIni)), 0.0);
	pE->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);

	GLdouble ladoActual = ladoIni;
	GLdouble angAcual= angIni;

	for (int i = 2; i < pE->numVertices; i++) {
		//nuevasCoords = mover(poliEspiral->vertices[i - 1].x, poliEspiral->vertices[i - 1].y, incrAng, incrLado);
		ladoActual = ladoActual + incrLado;
		angAcual = angAcual + incrAng;
		pE->vertices[i] = dvec3(pE->vertices[i - 1].x + ladoActual * cos(radians(angAcual)), pE->vertices[i - 1].y + ladoActual * sin(radians(angAcual)), 0.0);

		pE->colors[i] = dvec4(0.0, 1.0, 0.0, 1.0);
	}

	return pE;

}

//
//dvec2 Mesh::mover(GLuint x, GLuint y, GLdouble ang, GLdouble nuevoLado) {
//	dvec2 nuevoPunto;
//	nuevoPunto.x = x + nuevoLado * cos(radians(ang));
//	nuevoPunto.y = y + nuevoLado + sin(radians(ang));
//	return nuevoPunto;
//}

//-----------------------------------------------------------------------------------------
//--------------------------------GENERA PLANO NO TEXTURIZADO DE ANCHO W Y ALTURA H-----------------------------------------
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h) {
	Mesh* rectangle = new Mesh();
	rectangle->type = GL_TRIANGLE_STRIP;

	rectangle->numVertices = 4;
	rectangle->vertices = new dvec3[rectangle->numVertices];
	rectangle->colors = new dvec4[rectangle->numVertices];

	rectangle->vertices[0] = dvec3(-w / 2, -h / 2, 0.0);
	rectangle->vertices[1] = dvec3(w / 2, -h / 2, 0.0);
	rectangle->vertices[2] = dvec3(-w / 2, h / 2, 0.0);
	rectangle->vertices[3] = dvec3(w / 2, h / 2, 0.0);

	rectangle->colors[0] = dvec4(0.0, 0.0, 0.0, 1.0);
	rectangle->colors[1] = dvec4(0.0, 0.0, 0.0, 1.0);
	rectangle->colors[2] = dvec4(0.0, 0.0, 0.0, 1.0);
	rectangle->colors[3] = dvec4(0.0, 0.0, 0.0, 1.0);

	return rectangle;
}


//------------------------------------------------------------------------------------------------------
//--------------------------------GENERA RECTANGULO TEXTURIZADO Y PATRONADO-----------------------------------------
Mesh* Mesh::generateRectangleText(GLdouble w, GLdouble h, int x, int y) {
	Mesh* rT = generateRectangle(w, h);
	//X E Y VAN A SER EL NÚMERO DE VECES QUE SE REPITA LA TEXTURA
	rT->texCoords = new dvec2[rT->numVertices];
	rT->texCoords[0] = dvec2(0, 0);
	rT->texCoords[1] = dvec2(1+x, 0);
	rT->texCoords[2] = dvec2(0, 1+y);
	rT->texCoords[3] = dvec2(1+x, 1+y);

	return rT;
}
