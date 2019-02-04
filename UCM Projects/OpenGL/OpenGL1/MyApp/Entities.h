//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);
  
protected:
  Mesh* mesh = nullptr;
  Mesh* mesh2 = nullptr;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};

class Triangulo : public Entity
{
public :
	Triangulo(GLdouble r);
	~Triangulo() { };
	virtual void draw();

};

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB() {};
	virtual void draw();
};

class Rectangulo : public Entity {
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo() {};
	virtual void draw();
};
class TriPyramid : public Entity
{
public :
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() {};
	virtual void draw();
};

class ContCubo : public Entity
{
public :
	ContCubo(GLdouble l);
	~ContCubo() {};
	virtual void draw();
};

class Dragon : public Entity 
{
public:
	Dragon(GLuint numVert);
	~Dragon() {};
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();
};

class Poliespiral : public Entity {
public:
	Poliespiral(GLdouble x, GLdouble y, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() {};
	virtual void draw();
};

class Diablo :public Entity {
private:
	GLdouble altura;
	GLdouble angulo = 0.0;
public:
	Diablo(GLdouble r, GLdouble h);
	~Diablo() {};
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();
	Mesh* returnMesh();
	void rotaDiablo();
};

class Cubo : public Entity {
public :
	GLdouble lado;
	Cubo(GLdouble l);
	~Cubo() {};
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	//virtual void draw();
};


//-------------------------------------------------------------------------

#endif //_H_Entities_H_