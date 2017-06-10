#include "iostream"
#include "math.h"
#include "list"
#include "GL/glut.h"
using namespace std;
float xd1, yd1, xd2, yd2;
class Point {
public:
  float x;
  float y;
  Point (float x, float y){
    this->x = x;
    this->y = y;
  }
};
list<Point> subjectPolygon;
int initializePolygon()
{
  subjectPolygon.push_back(Point(100, 100));
  subjectPolygon.push_back(Point(100, 150));
  subjectPolygon.push_back(Point(200, 150));
  subjectPolygon.push_back(Point(200, 100));
}

void init(){
  glutInitWindowSize(800,600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Lines");
  gluOrtho2D(0, 800, 0, 600);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}
void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0, 0, 1);

  glBegin(GL_POLYGON);
  for(list<Point>::iterator it = subjectPolygon.begin();it!=subjectPolygon.end();it++){
    Point P = *it;
    glVertex2f(P.x, P.y);
  }
  glEnd();
  glFlush();
}
// scale polygon
list<Point> scale(list<Point> outputList, float scale_x, float scale_y){
  list<Point> inputList = outputList;
  outputList.clear();
  for(list<Point>::iterator it = inputList.begin();it!=inputList.end();it++){
    Point p = *it;
    outputList.push_back(Point(scale_x * p.x, scale_y * p.y));
  }
  return outputList;
}

// translate polygon
list<Point> translate(list<Point> outputList, float translate_x, float translate_y){
  list<Point> inputList = outputList;
  outputList.clear();
  for(list<Point>::iterator it = inputList.begin();it!=inputList.end();it++){
    Point p = *it;
    outputList.push_back(Point(translate_x + p.x, translate_y + p.y));
  }
  return outputList;
}
// rotate polygon
list<Point> rotate(list<Point> outputList, float degree){
  list<Point> inputList = outputList;
  outputList.clear();
  float theta = degree*3.14 / 180;
  for(list<Point>::iterator it = inputList.begin();it!=inputList.end();it++){
    Point p = *it;
    float x = p.x *cos(theta) + p.y*sin(theta);
    float y = p.x * -sin(theta) + p.y*cos(theta);
    outputList.push_back(Point(x, y));
  }
  return outputList;
}
void transform()
{
    list<Point> outputList = subjectPolygon;
    outputList = scale(outputList,2, 2);
    // outputList = translate(outputList, 100, 300);
    // outputList = rotate(outputList, -20);
    subjectPolygon = outputList;
    display();
}
// press t to transform the polygon
void key(unsigned char c, int x, int y){
  if(c=='t'){
    transform();
    glFlush();
  }
}
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  init();
  initializePolygon();
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  glutMainLoop();
  return 0;
}

