#include "iostream"
#include "GL/glut.h"
#include "math.h"
#define PI 3.14
#define car1XInc .1;
#define car2XInc .11;
#define car1RotInc .05;
#define car2RotInc .6;
using namespace std;
float car1X = 0;
float car2X = 0;
float car1Rot = 0;
float car2Rot = 0;
float circleRadius = 20;
void drawCircle(int xc, int yc, float r){
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; i++) {
    float theta = i*PI/180;
    glVertex2f(xc+r*cos(theta), yc+r*sin(theta));
  }
  glEnd();
}
void drawSpokes(int xc, int yc, float r, float angle){
  int theta = angle;
  theta%=360;
  int end = theta;
  glBegin(GL_LINES);
  for (; theta < 360+end; theta+=30) {
    glVertex2f(xc, yc);
    float t = theta*PI/180;
    glVertex2f(xc+r*cos(t), yc+r*sin(t));
  }
  glEnd();
}
void drawCar(int xOffset, int yOffset, int angle){
  glBegin(GL_LINE_LOOP);
    glVertex2f(xOffset, yOffset);
    glVertex2f(xOffset, yOffset+60);
    glVertex2f(xOffset+90, yOffset+60);
    glVertex2f(xOffset+125, yOffset+120);
    glVertex2f(xOffset+205, yOffset+120);
    glVertex2f(xOffset+240, yOffset+60);
    glVertex2f(xOffset+340, yOffset+60);
    glVertex2f(xOffset+340, yOffset);
    glVertex2f(xOffset+250, yOffset);
    for (int i = 0; i < 180; i++) {
      float theta = i*PI/180;
      glVertex2i(xOffset+230+(circleRadius+5)*cos(theta), yOffset+(circleRadius+5)*sin(theta));
    }
    glVertex2f(xOffset+210, yOffset);
    glVertex2f(xOffset+110, yOffset);
    for (int i = 0; i < 180; i++) {
      float theta = i*PI/180;
      glVertex2i(xOffset+90+(circleRadius+5)*cos(theta), yOffset+(circleRadius+5)*sin(theta));
    }
  glEnd();
    drawCircle(xOffset+90, yOffset, circleRadius);
    drawCircle(xOffset+230, yOffset, circleRadius);
    drawSpokes(xOffset+90, yOffset, circleRadius, angle);
    drawSpokes(xOffset+230, yOffset, circleRadius, angle);
}
void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,1,1);
  drawCar(car1X, 100, car1Rot);
  drawCar(car2X, 400, car2Rot);

  car1X+=car1XInc;
  car2X+=car2XInc;
  car1Rot-=car1RotInc;
  car2Rot-=car2RotInc;

  glutSwapBuffers();
}
void init(){
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(800,600);
  glutCreateWindow("Car");
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
