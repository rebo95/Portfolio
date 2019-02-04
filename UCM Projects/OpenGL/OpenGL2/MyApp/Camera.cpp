#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
   w = aw; 
   h = ah; 
   set(); 
 }

 void Viewport::setPosition(GLint vp_x, GLint vp_y) {
	 x = vp_x;
	 y = vp_y;
	 set();
 }
 //-------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
//-------------------------------------------------------------------------

void Camera::setAZ() 
{
  eye= dvec3(0, 0, 500);
  look= dvec3(0, 0, 0);
  up= dvec3(0, 1, 0);

//CODIGO ORIGINAL, ESTA SERÍA LA MANERA DE TRABAJAR Y ACTUALIZAR TODAS LAS COMPONENTES DE LA CÁMARA
  //SIN EMBARGO NOSOTROS HEMOS DECLARADO LAS VARIABLES FRONT , RIGH Y UPLOCAL PARA TRABAJAR DE MANERA MÁS CÓMODA, SON ESTAS LAS QUE TENEMOS QUE ACTUALIZAR EN TODO MOMENTO PARA QUE NO SE 
  // PRODUZCAN SALTO INESPERADOS A LA HORA DE HACER LOS DIFERENTES MOVIMIENTOS DE LAS CÁMARAS.
  ////n = normalize(eye - look);
  ////u = normalize(cross(up, n));
  ////v = cross(n, u);
  ////front = -n;
  ////upLocal = v;
  ////right = u;

  front = -normalize(eye - look);
  right = normalize(cross(front, up));
  upLocal = cross(right, front);

  //AQUÍ TENEMOS FRONT RIGHT Y UPLOCAL YA QUE MODIFICAMOS LA MATRIZ DE VISTA, NOS INTERESA ACTUALIZAR LOS ÁNGULOS DESPEJANDO DE LAS ECUACIONES 
  pitch_ = degrees(asin(front.y)); // HACE REFERENCIA AL ÁNGULO DE CABECEO ( CUANDO SUBE Y BAJA EL MORRO DEL AVIÓN)
  yaw_ = degrees(asin(front.x / cos(radians(pitch_))));  // HACE REFERENCIA AL ÁNGULO DE GUIÑADA, EL MOVIMIENTO HORIZONTAL DEL AVIÓN SIN ROTAR SOBRE SI MISMO ( COMO SI MOVIÉSEMOS LOS HOMBROS ALANTE Y ATRÁS)
  roll_ = degrees(asin(up.x)); // HACE REFERENCIA AL ALABEO , O MOVIMIENTO NECESARIO PARA GIRAR DE LOS AVIONES , INCLINACIÓN HACIA UNO DE LOS LADOS.

  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye= dvec3(500, 500, 500);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);

  front = -normalize(eye-look);
  right = normalize(cross(front, up));
  upLocal = cross(right, front);

  pitch_ = degrees(asin(front.y));
  yaw_ = degrees(asin(front.x/cos(radians(pitch_))));
  roll_ = degrees(asin(up.x));

  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	rotatePY(a, 0);
	//viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(5.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	rotatePY(0, a);
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 5.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	rolling(a);
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 5.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	glMatrixMode(GL_PROJECTION);
	if (ortho_) {
		nearVal = 1;
		farVal = 10000;//seteamos la perspectiva a ortogonal 
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}
	else {
		nearVal = 300;
		farVal = 10000;//seteamos la perspectiva a perspectiva
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}

	//esto lo hacemos para que funcione el zoom para las dos perspectivas
  glLoadMatrixd(value_ptr(projMat));
  glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

void Camera::moveFB(GLdouble cs) {
	eye = eye + (front * cs); // donde cs hace relación a la velocidad de desplazamiento a la que queremos que se mueva la cámara
	look = look + (front*cs);
	viewMat = lookAt(eye, look, up);
}

void Camera:: moveLR(GLdouble cs) {
	eye = eye + (right * cs);
	look = look + (right * cs); // donde cs hace relación a la velocidad de desplazamiento a la que queremos que se mueva la cámara
	viewMat = lookAt(eye, look, up);
}

void Camera::moveUD(GLdouble cs) {
	eye = eye + (upLocal * cs);
	look = look + (upLocal * cs);// donde cs hace relación a la velocidad de desplazamiento a la que queremos que se mueva la cámara
	viewMat = lookAt(eye, look, up);
} // Up / Down 

void Camera:: rotatePY(GLdouble incrPitch, GLdouble incrYaw) {
	pitch_ += incrPitch; yaw_ += incrYaw;
	if (pitch_ > 89.5) pitch_ = 89.5;
	if (pitch_ < -89.5) pitch_ = -89.5;
	//pitch_ = (GLint)pitch_ % 360;
	//yaw_ = (GLint)yaw_ % 360;


	//AQUÍ TENEMOS LOS ÁNGULOS YA QUE MODIFICAMOS SON LOS QUE MODIFICAMOS DIRECTAMENTE, NOS INTERESA ACTUALIZAR LOS VALORES DE LA MATRIZ DE VISTA FRONT RIGHT Y UPLOCAL DESPJANDO DE LAS ECUACIONES
	front.x = sin(radians(yaw_)) * cos(radians(pitch_));
	front.y = sin(radians(pitch_));
	front.z = -cos(radians(yaw_)) * cos(radians(pitch_));
	front = glm::normalize(front);

	right = normalize(cross(up, -front));
	upLocal = cross(-front, right);

	look = eye + front;
	viewMat = lookAt(eye, look, up);

}

void Camera:: rolling(GLdouble incrRoll) {
	roll_ += incrRoll;
	up.y = cos(radians(roll_));
	up.x = sin(radians(roll_));

	//AQUÍ NO ACTUALIZAMOS EL FRONT PORQUE NO ES NECESARIO, YA QUE ROTAMOS PRECISAMENTE SOBE ESE EJE 
	right = normalize(cross(up, -front));
	upLocal = cross(-front, right); //vector que apunta hacia arriba en las coordenadas locales

	viewMat = lookAt(eye, look, up);
}

void Camera::setPrj() {
	glMatrixMode(GL_PROJECTION);
	if (!ortho_) {
		nearVal = 1;
		farVal = 10000;
		projMat = ortho(xLeft, xRight, yBot, yTop, nearVal, farVal);
		ortho_ = true;
	}
	else
	{
		nearVal = 300;
		farVal = 10000;
		projMat = frustum(xLeft, xRight, yBot, yTop, nearVal, farVal);
		ortho_ = false;
	}
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}