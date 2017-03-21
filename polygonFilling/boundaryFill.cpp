#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <list>
#include <queue>
#include <set>
#include <iostream>
using namespace std;
static int DEBUGG = 1;
class Point
{
public:
	float x;
	float y;
	Point();
	Point(float x1, float y1){
		x=x1;
		y=y1;
	}
};
std::list<Point> subjectPolygon ;
int ww = 600, wh = 500, ymax=-1000 , ymin=1000;
float bgCol[3] = {0.0, 0.0,0.0};
float boundaryCol[3] = {1.0,0.0,0.0};
float fillCol[3] = {0.0,0.0,1.0};
set<Point> dfs;
void setPixel(int pointx, int pointy, float f[3])
{
       glBegin(GL_POINTS);
            glColor3fv(f);
            glVertex2i(pointx,pointy);
       glEnd();
       glFlush();
}
void getPixel(int x, int y, float pixels[3])
{
     glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
}
void initPolygon(){
	int n, x, y;
	cout<<"Enter number of vertices : ";
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x>>y;
		ymax = ymax<y ? y: ymax;
		ymin = ymin>y ? y: ymin;
		subjectPolygon.push_back(Point(x, y));
	}
}
void drawPolygon()
{
       glColor3f(1.0, 0.0, 0.0);
       glBegin(GL_LINE_LOOP);
			 for (Point point : subjectPolygon)
			 	glVertex2i(point.x,point.y);
       glEnd();
       glFlush();
}
void display()
{
       glClearColor(0.0,0.0,0.0,1.0);
       glClear(GL_COLOR_BUFFER_BIT);
       drawPolygon();
       glFlush();
}
int checkPoint(Point p, float oldcolor[3], float newcolor[3]){
	float color[3];
	getPixel(p.x,p.y,color);
  int isOldColor = color[0]==oldcolor[0] && (color[1])==oldcolor[1] && (color[2])==oldcolor[2] ;
	int isNewColor = (color[0]==newcolor[0]) && (color[1]==newcolor[1]) && (color[2]==newcolor[2]) ;
	return isOldColor || isNewColor ;
}
void boundaryFill(Point seed,float oldcolor[3],float newcolor[3])
{
      queue<Point> Q;
			Q.push(seed);
			while(!Q.empty()){
				seed = Q.front();
				Q.pop();
				Point west = seed;
				Point east = seed;
				while(!checkPoint(west,oldcolor,newcolor))
					west = Point(west.x-1, west.y);
				while(!checkPoint(east,oldcolor,newcolor))
					east = Point(east.x+1, east.y);
				for(int i = west.x+2;i<=east.x;i++){
					setPixel(i, seed.y, newcolor);
				}
				if(west.x==east.x)
					continue;
				Point north((east.x+west.x)/2, seed.y+1);
				Point south((east.x+west.x)/2, seed.y-1);
				// if(!checkPoint(north,oldcolor,newcolor))
					Q.push(north);
				// if(!checkPoint(south,oldcolor,newcolor))
					Q.push(south);
			}
}
void mouse(int btn, int state, int x, int y)
{
       if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          boundaryFill(Point(x, wh-y),boundaryCol,fillCol);
}
void myinit()
{
      glViewport(0,0,ww,wh);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
      // glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
       glutInit(&argc,argv);
       glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
       glutInitWindowSize(ww,wh);
       glutCreateWindow("Polyon Boundary Fill");
			 initPolygon();
       glutDisplayFunc(display);
       myinit();
       glutMouseFunc(mouse);
       glutMainLoop();
       return 0;
}
