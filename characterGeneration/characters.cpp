#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <GL/glut.h>
#include <unistd.h>
#include <vector>
#define PI 3.14159
using namespace std;
typedef  pair<int, int> iPair;
int con = 100, base = 200, width = 10, height = 100, diff = 5;
float radius = 10;
float yes[3] = {1, 1, 0};
float no[3] = {0, 0, 0};
int c[16][7]={
  {1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 1, 1, 0, 0},
  {1, 0, 1, 1, 0, 1, 1},
  {0, 0, 1, 1, 1, 1, 1},
  {0, 1, 0, 1, 1, 0, 1},
  {0, 1, 1, 0, 1, 1, 1},
  {1, 1, 1, 0, 1, 1, 1},
  {0, 0, 1, 1, 1, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 0, 1},
  {1, 1, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 0},
  {1, 0, 0, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 1},
  {1, 1, 1, 0, 0, 0, 1}
};
vector<iPair> endPoints = { {200, 200}, {200, 300}, {205, 400}, {280, 300}, {280, 200}, {205, 200}, {205, 295} };
bool horizontalOrientation[7] = {false, false, true, false, false, true, true};
void drawLine(float x1, float y1, float color[3], bool horizontal){
  float x2 = x1 , y2 = y1;
  if(horizontal)
    x2 = x1+70;
  else
    y2 = y1+90;
  glColor3fv(color);
  // glPointSize(100);
  glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
  glEnd();
  glFlush();
}
void draw7segment(void){
  for (size_t i = 0; i < 16; i++) {
    for (size_t j = 0; j < 7; j++) {
      if(c[i][j])
      drawLine(endPoints[j].first, endPoints[j].second, yes, horizontalOrientation[j]);
        // drawRect(yes, j);
      else
        drawLine(endPoints[j].first, endPoints[j].second, no, horizontalOrientation[j]);
        // drawRect(no, j);
    }
    usleep(2000 * 1000); // takes microseconds
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
  glutDisplayFunc(draw7segment);
  glutMainLoop();
  return 0;
}
