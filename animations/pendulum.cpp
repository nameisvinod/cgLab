#include "iostream"
#include "GL/glut.h"
#include "math.h"
#define PI 3.14
using namespace std;
float centerX = 400, centerY = 500, lineRadius = 200, circleRadius = 20;
float angle = 240, inc = .03;
void drawCircle(int xc, int yc, float r){
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; i++) {
    float theta = i*PI/180;
    glVertex2f(xc+r*cos(theta), yc+r*sin(theta));
  }
  glEnd();
}
void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,1,1);
  drawCircle(centerX, centerY, circleRadius);

  double radian = angle*PI/180;
  float x2 = centerX +  lineRadius * cos((double) radian);
  float y2 = centerY + lineRadius * sin((double) radian);
  drawCircle(x2, y2, circleRadius);
  if (angle>300) {
    angle = 300;
    inc = -inc;
  }
  if (angle<240) {
    angle = 240;
    inc = -inc;
  }
  angle+=inc;
  glBegin(GL_LINES);
    glVertex2f(centerX, centerY);
    glVertex2f(x2, y2);
  glEnd();
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
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutMainLoop();
  return 0;
}
