#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
double X1, Y1, X2, Y2;

float round_value(float v){
  return floor(v + 0.5);
}
void LineDDA(void){
  double dx=(X2-X1);
  double dy=(Y2-Y1);
  double steps;
  float xInc,yInc,x=X1,y=Y1;

  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  glVertex2d(x,y);
  int k;
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    glVertex2d(round_value(x), round_value(y));
  }
  glEnd();
  glFlush();
}
void Init()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("DDA_Line");
  glClearColor(0.0,0.0,0.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}
int main(int argc, char **argv)
{
  cout<<"Enter two end points of the line to be drawn:\n";
  cout<<"\nEnter Point1( X1 , Y1):\n";
  cin>>X1>>Y1;
  cout<<"\nEnter Point2( X2 , Y2):\n";
  cin>>X2>>Y2;

  glutInit(&argc,argv);
  Init();
  glutDisplayFunc(LineDDA);
  glutMainLoop();
  return 0;
}