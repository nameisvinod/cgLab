#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
double X1, Y1, X2, Y2;

void LineBresenham(void){
  double dx = fabs(X2 - X1);
  double dy = fabs(Y2 - Y1);
  double p = 2 * dy - dx;
  double twoDy = 2 * dy;
  double twoDyMinusDx = 2 * (dy-dx);
  double x,y;
  if (X1 > X2){
    x = X2;
    y = Y2;
    X2 = x;
  }else{
    x = X1;
    y = Y1;
  } 
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  glVertex2d(x,y);
  while(x<X2){
    x++;
    if(p<0)
      p += twoDy;
    else{
      y++;
      p += twoDyMinusDx;
    }
    glVertex2d(x,y);
  } 
  glEnd();
  glFlush();
}
void Init()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Bresenham_Line");
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
  glutDisplayFunc(LineBresenham);
  glutMainLoop();
  return 0;
}