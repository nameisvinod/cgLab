#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
double xCenter, yCenter, r;

void setPixel(GLint x,GLint y)
{
  glBegin(GL_POINTS);
  glVertex2d(x,y);
  glEnd();
}
void plot8(double x , double y){
    setPixel(xCenter+x,yCenter+y);
    setPixel(xCenter+y,yCenter+x);  
    setPixel(xCenter-x,yCenter+y);
    setPixel(xCenter+y,yCenter-x);
    setPixel(xCenter-x,yCenter-y);
    setPixel(xCenter-y,yCenter-x);
    setPixel(xCenter+x,yCenter-y);
    setPixel(xCenter-y,yCenter+x);
}
void midPointCircle(void){
  int x=0,y=r;
  int p = 3/2 - r;    
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 1 ,0, 0); 
  while(x<=y){
    plot8(x, y);
    if (p<0)
      p += (2*x)+1;
    else {
      p += (2*(x-y))+1;
      y -= 1;
    }
    x++;
  }
  glFlush();
}
void Init()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("MidPoint Circle");
  glClearColor(0.0,0.0,0.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}
int main(int argc, char **argv)
{
  cout<<"Enter the centre and radius\n";
  cin>>xCenter>>yCenter>>r;

  glutInit(&argc,argv);
  Init();
  glutDisplayFunc(midPointCircle);
  glutMainLoop();
  return 0;
}