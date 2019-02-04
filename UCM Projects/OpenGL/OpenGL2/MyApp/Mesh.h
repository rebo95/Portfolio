//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:

//LAS NUEVAS MALLAS SE EMPIEZAN DECLARANDO DESDE AQUÍ  
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generateTriangle(GLdouble r);
  static Mesh* generateTriangleRGB(GLdouble r);
  static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
  static Mesh* generateContCubo(GLdouble l);
  static Mesh* generaDragon(GLuint numVert);
  static Mesh* generaPoliespiral(GLdouble x, GLdouble y, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
  static Mesh* generateRectangle(GLdouble w, GLdouble h);
  static Mesh* generateCubeText(GLdouble l);
  static Mesh* generateRectangleText(GLdouble w, GLdouble h, int x, int y);
  static Mesh* generateTriPyramidText(GLdouble r, GLdouble h);
  
 
  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;

   glm::dvec2 * texCoords = nullptr;

private:
//	dvec2 mover(GLuint x, GLuint y, GLdouble ang, GLdouble incrLado);
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_