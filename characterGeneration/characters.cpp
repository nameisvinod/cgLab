#include <iostream>
#include <string>
#include <math.h>
#include <GL/glut.h>
#include <unistd.h>
#define PI 3.14159
using namespace std;
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
int segment[7][8]={
  {base, base, base+width, base, base+width, base+height, base, base+height},
  {base, base+2*width+height, base+width, base+2*width+height, base+width, base+2*width+2*height, base, base+2*width+2*height},
  {base, base+2*width+2*height+diff, base+con+width, base+2*width+2*height+diff, base+con+width, base+2*width+2*height+diff+width, base, base+2*width+2*height+diff+width },
  {base+con, base+2*width+height, base+width+con, base+2*width+height, base+width+con, base+2*width+2*height, base+con, base+2*width+2*height},
  {base+con, base, base+width+con, base, base+width+con, base+height, base+con, base+height},
  {base, base-width+diff, base+con+width, base-width+diff, base+con+width, base-2*width+diff, base, base-2*width+diff },
  {base, base+width+height-diff, base+con+width, base+width+height-diff, base+con+width, base+2*width+height-diff, base, base+2*width+height-diff },
  };
void drawRect(float color[3], int i){
  glColor3fv(color);
    glBegin(GL_POLYGON);
        glVertex2i(segment[i][0],segment[i][1]);
        glVertex2i(segment[i][2],segment[i][3]);
        glVertex2i(segment[i][4],segment[i][5]);
        glVertex2i(segment[i][6],segment[i][7]);
    glEnd();
  glFlush();
}
void draw7segment(void){
  for (size_t i = 0; i < 16; i++) {
    for (size_t j = 0; j < 7; j++) {
      if(c[i][j])
        drawRect(yes, j);
      else
        drawRect(no, j);
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
