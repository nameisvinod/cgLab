#include <GL/glut.h>
#include <math.h>
#include "iostream"
using namespace std;

float rot = 0;
float angle = 135;
float inc = 1.0;

void drawCircle(float segments, float radius, float sx, float sy)
{
  float theta = 2 * 3.1415926 / segments;
  float tan_factor = tanf(theta);
  float radial_factor = cosf(theta);
  float x = radius;
  float y = 0;

  int cache_pt = 0;
  double cache_x;
  double cache_y;

  glBegin(GL_LINES);
  for (int ii = 0; ii < segments; ii++) {
    if(!cache_pt) {
      cache_x = x+sx;
      cache_y = y+sy;
      cache_pt = 1;
    } else {
      //glVertex2f(cache_x,cache_y);
      glVertex2f(x + sx, y + sy);
      cache_x = x+sx;
      cache_y = y+sy;
    }
    float tx = -y;
    float ty = x;
    x += tx * tan_factor;
    y += ty * tan_factor;
    x *= radial_factor;
    y *= radial_factor;
  }
  glEnd();
}


void drawCircles(float x1,float y1,double angle) {
  float segments = 25;
  float radius = 1.0;
  // Draw the original circle
  drawCircle(segments,radius,x1,y1);

  // Draw the pendulum circle
  double radian = angle*3.14/180;
  float m = (double)tan((double)radian);
  float y2 = 10 * cos((double) radian);
  float x2 = 10 * sin((double) radian);
  drawCircle(segments,radius,x2,y2);

  glBegin(GL_LINES);
  glVertex2f(x1,y1);
  glVertex2f(x2,y2);
  glEnd();

}

void display(void) {
  glClearColor (0.0,0.0,0.0,1.0);
  glClear (GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(-10,0,-30);
  glColor3f(1,1,1);

  if (angle>225) {
    angle = 225;
    inc = -inc;
  }
  if (angle<135) {
    angle = 135;
    inc = -inc;
  }
  angle += inc;
  drawCircles(0,0,angle);
  glutSwapBuffers();

}

void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
  glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  if(key =='q')
    exit(0);
}

int main (int argc, char **argv) {
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE);
  glutInitWindowSize (1200, 800);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("A Pendulum");

  glutDisplayFunc (display);
  glutIdleFunc (display);
  glutReshapeFunc (reshape);
  glutKeyboardFunc (keyboard);
  glutMainLoop ();
  return 0;
}
