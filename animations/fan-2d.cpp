#include "iostream"
#include "GL/glut.h"
#include "math.h"
#define PI 3.14
using namespace std;
float centerX = 400, centerY = 300, lineRadius = 200, circleRadius = 20;
float angle = 240, inc = .1;

void drawCircle(int xc, int yc, float r){
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; i++) {
    float theta = i*PI/180;
    glVertex2f(xc+r*cos(theta), yc+r*sin(theta));
  }
  glEnd();
}
void drawArm(float rotAngle){
  float radian1 = (rotAngle+10) *PI/180;
  float x1 = centerX +  lineRadius * cos((double) radian1);
  float y1 = centerY + lineRadius * sin((double) radian1);

  float radian2 = (rotAngle-10)*PI/180;
  float x2 = centerX +  lineRadius * cos((double) radian2);
  float y2 = centerY + lineRadius * sin((double) radian2);

  glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(centerX, centerY);
    glVertex2f(x2, y2);
  glEnd();
}
void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(1);
  glColor3f(1,1,1);
  drawCircle(centerX, centerY, circleRadius);
  drawArm(angle);
  drawArm(angle-120);
  drawArm(angle-240);
  angle = angle==360?0:angle+inc;
  glutSwapBuffers();
}
void init(){
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(800,600);
  glutCreateWindow("Pendulum");
  glClearColor(0.0,0.0,0.0,1.0);
  gluOrtho2D(0 , 800 , 0 , 600);
  glClear(GL_COLOR_BUFFER_BIT);
}
void keyBoard(unsigned char c, int x, int y){
  switch(c){
    case 'a': inc+=0.1;break;
    case 'd': if(inc>0) inc-=0.1; break;
    case 'q': exit(0);
    default: break;
  }
}
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(keyBoard);
  glutMainLoop();
  return 0;
}
