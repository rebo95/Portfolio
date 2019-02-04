//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>


//Pablo Martín García
//Aaron Reboredo Vázquez


#include <GL/freeglut.h>
#include "Camera.h"
#include "Scene.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------
glm::dvec2 mCoord;
bool anim = true;
// Viewport position and size
GLuint deltaTime = 5;
GLuint last_update_tick;
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Scene entities
Scene scene(&camera);   

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void update();
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 

  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); 
  //glEnable(GL_BLEND);
  // | GLUT_STENCIL 

  
  int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutIdleFunc(update);
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 
  scene.init();    // after creating the context
   
  glutMainLoop(); 
    
  //cin.sync();   cin.get();
  glutDestroyWindow(win);  // Destroy the context 

  return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
  scene.render();   
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.setSize(newWidth, newHeight);  
  // Resize Scene Visible Area 
  camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.scale(+0.01);   // zoom in  
    break;
  case '-':
    camera.scale(-0.01);   // zoom out
    break;
  case 'l':
	  camera.set3D(); 
	  break;
  case 'o':
	  camera.setAZ();
	  break;
  case 'x':
	 // //scene.giveDiablo()->rotaDiablo();
	 scene.giveDiabloText()->rotaDiabloText();
	 break;
  case 'F': {
	  Textures image;
	  image.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)); //necesario para que la imagen se guarde correctamente y se
	  //pueda visualizar desde el archivo
	  image.save("..\\Bmps\\picture.bmp");
  }
	break;
	case 'f': {
		scene.getFoto()->getPicture();
  }
	  break;
  case 'a':
	  camera.moveLR(-20);
	  break;
  case 'd':
	  camera.moveLR(20);
	  break;
  case 'w':
	  camera.moveFB(20);
	  break;
  case 's':
	  camera.moveFB(-20);
	  break;
  case 'u':
	  camera.moveUD(20);
	  break;
  case 'j':
	  camera.moveUD(-20);
	  break;
  case 'p':
	  camera.setPrj();
	  break;
  case 'z':
	  anim = !anim;
	  break;
  case 'B':
	  scene.getLight()->disable();
	  break;
  case 'b':
	  scene.getLight()->enable();
	  break;
  case 'N':
	  scene.getFocalLight()->disable();
	  break;
  case 'n':
	  scene.getFocalLight()->enable();
	  break;
  case 'M':
	  scene.getEsferaDeLuz()->giveLight()->disable();
	  break;
  case 'm':
	  scene.getEsferaDeLuz()->giveLight()->enable();
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.pitch(1);   // rotate 1 on the X axis
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(1);     // rotate 1 on the Y axis 
    break;
  case GLUT_KEY_UP:
    camera.roll(1);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
    camera.roll(-1);   // rotate -1 on the Z axis
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		mCoord.x = x;
		mCoord.y = -y;
	}
}

void motion(int x, int y) {
	glm::dvec2 mOffset = mCoord;
	mCoord = glm::dvec2(x,/* glutGet(GLUT_WINDOW_HEIGHT)*/ - y);
	mOffset = (mCoord - mOffset)*0.05;
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}


void update(){
if (anim){
		deltaTime = glutGet(GLUT_ELAPSED_TIME) - last_update_tick;
		scene.update(deltaTime);
		last_update_tick = glutGet(GLUT_ELAPSED_TIME);
		glutPostRedisplay();
	}
}