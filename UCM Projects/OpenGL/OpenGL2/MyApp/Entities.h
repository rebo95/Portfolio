//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Textures.h"


//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);
  virtual void update(GLuint timeElapsed) {};

  
protected:
  Mesh* mesh = nullptr;
  Mesh* mesh2 = nullptr;
  Textures texture;
  Textures texture2;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//---------------------------------------------------------------------------------
//--------------------------------RGB AXES-----------------------------------------
class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};
//---------------------------------------------------------------------------------
//--------------------------------TRIANGULO-----------------------------------------
class Triangulo : public Entity
{
public :
	Triangulo(GLdouble r);
	~Triangulo() { };
	virtual void draw();
};
//---------------------------------------------------------------------------------
//--------------------------------TRIANGULORGB-----------------------------------------
class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB() {};
	virtual void draw();
};
//---------------------------------------------------------------------------------
//--------------------------------RECTANGULO-----------------------------------------
class Rectangulo : public Entity {
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo() {};
	virtual void draw();
};
//----------------------------------------------------------------------------------------------
//--------------------------------RECTANGULO TEXTURIZADO-----------------------------------------
class RectanguloText : public Entity {
public :
	RectanguloText(GLdouble w, GLdouble h, int repeticiones_patron_x , int repeticiones_patron_y, int posX, int posY, int posZ);
	~RectanguloText() {};
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
protected:
	int iniX, iniY, iniZ;
};

//----------------------------------------------------------------------------------------------------------------
//--------------------------------PIRAMIDE NO TEXTURIZADA----------------------------------------------------------------
class TriPyramid : public Entity
{
public :
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() {};
	virtual void draw();
};
//----------------------------------------------------------------------------------------------------------------
//--------------------------------PIRAMIDE TEXTURIZADA----------------------------------------------------------------
//utiliza el mesh de la tripirámide
class TriPyramidText : public Entity
{
public:
	TriPyramidText(GLdouble r, GLdouble h);
	~TriPyramidText() {};
	virtual void draw();
};
//----------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO NO TEXTURIZADO----------------------------------------------------------------
class ContCubo : public Entity
{
public :
	ContCubo(GLdouble l);
	~ContCubo() {};
	virtual void draw();
};
//----------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO TEXTURIZADO----------------------------------------------------------------
//utiliza el mesh del cubo no texturizado
class CuboText : public Entity {
public:
	CuboText(GLdouble l);
	~CuboText() {};
	virtual void draw();
};
//----------------------------------------------------------------------------------------------------------------
//--------------------------------DRAGON (POINT GENERATED)--------------------------------------------------------
class Dragon : public Entity 
{
public:
	Dragon(GLuint numVert);
	~Dragon() {};
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();
};
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------POLIESPIRAL-------------------------------------------------------------------
class Poliespiral : public Entity {
public:
	Poliespiral(GLdouble x, GLdouble y, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() {};
	virtual void draw();
};
//--------------------------------------------------------------------------------------------------------------
//--------------------------------DIABOLO NO TEXTURIZADO--------------------------------------------------------
class Diablo :public Entity {
private:
	GLdouble altura;
	GLdouble angulo = 0.0;
	GLdouble speed = 0.0;

public:
	Diablo(GLdouble r, GLdouble h);
	~Diablo() {};
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();
	Mesh* returnMesh();
	void rotaDiablo();
	virtual void update(GLuint timeElapsed);
};

//------------------------------------------------------------------------------------------------------------
//--------------------------------DIABOLO TEXTURIZADO--------------------------------------------------------
class DiabloText : public Entity {

private:
	GLdouble altura;
	GLdouble angulo = 0.0;
	GLdouble speed =0.25;// nos permiten controlar el ángulo de giro del objeto 
public:
	DiabloText(GLdouble r, GLdouble h, int x, int y, int z);//posiciones iniciales del elemento, se utilizara un translate inicial para ello
	~DiabloText() {};
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void draw();
	Mesh* returnMesh();
	void rotaDiabloText();//método que nos permite girar el diabolo
	virtual void update(GLuint timeElapsed);

private:
	int iniX, iniY, iniZ;
};

//------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO_TAPA_RELLENO_TEXTURA2--------------------------------------------------
//utiliza el mesh del cubotext
class Cubo : public Entity {
public :
	GLdouble lado;
	Cubo(GLdouble l, int x,int y, int z);
	~Cubo() {};
	virtual void draw();
	virtual void draw2();
	virtual void render(glm::dmat4 const& modelViewMat);
	//virtual void draw();
private:
	int iniX, iniY, iniZ;
};

//------------------------------------------------------------------------------------------------------------
//--------------------------------CUBO DE CRISTAL-----------------------------------------
class GlassPot :public Entity {
	public:
		GLdouble lado;
		GlassPot(GLdouble l, int x, int y, int z);
		~GlassPot(){}
		virtual void draw();
		virtual void render(glm::dmat4 const& modelViewMat);
private:
	int iniX, iniY, iniZ;
};

//------------------------------------------------------------------------------------------------------------
//--------------------------------HIERBA-----------------------------------------
class Grass : public Entity {
public :
	Grass(GLdouble w, GLdouble h, int x, int y, int posX, int posY, int posZ);
	~Grass() {};
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	int iniX, iniY, iniZ;
};

//------------------------------------------------------------------------------------------------------------
//--------------------------------FOTO(HEREDA DE RECTANGULOTEXTURIZADO-----------------------------------------
class Foto : public RectanguloText {
public:
	Foto(GLdouble w, GLdouble h, int x, int y, int posX, int posY, int posZ);
	~Foto() {};
	virtual void update(GLuint timeElapsed);
	virtual void getPicture();
private:
	GLuint tempo;
};


//-------------------------------------------------------------------------

#endif //_H_Entities_H_