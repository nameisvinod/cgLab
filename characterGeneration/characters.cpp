#include <iostream>
#include <string>
#include <math.h>
#include <GL/glut.h>
#define PI 3.14159
using namespace std;
float radius = 10, con = 0;
float yes[3] = {0, 1, 1};
float no[3] = {0, 0, 0};
int a[13][9];
void readBitmap(){
  for (size_t i = 0; i < 13; i++)
    for (size_t j = 0; j < 9; j++)
        cin>>a[i][j];
}
void drawFilledCircle(float radius, float x, float y, float color[3]){
	int triangleAmount = 20; //# of triangles used to draw circle
	GLfloat twicePi = 2.0f * PI;
  glColor3fv(color);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(int i = 0; i <= triangleAmount;i++)
      glVertex2f(x + (radius * cos(i *  twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	glEnd();
  glFlush();
}
void generateCharacters(){
    int x =150, y= 400;
  for (size_t i = 0; i < 13; i++) {
    for (size_t j = 0; j < 9; j++) {
      if(a[i][j])
        drawFilledCircle(radius, x, y, yes);
      else
        drawFilledCircle(radius, x, y, no);
      x+=2*(radius-con);
    }
    y-=2*(radius-con);
    x = 150;
  }
}
void Init()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("BFS Traversal");
  glClearColor(0.0,0.0,0.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
  glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  Init();
  readBitmap();
  glutDisplayFunc(generateCharacters);
  glutMainLoop();
  return 0;
}
