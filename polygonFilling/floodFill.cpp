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
int ww = 600, wh = 500;
float bgCol[3] = {0.0, 0.0,0.0};
float intCol[3] = {1.0,0.0,0.0};
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
		 cout<<"pixels : "<<pixels[0]<<"	:	"<<pixels[1]<<"	:	"<<pixels[2]<<"	:	"<<endl;

}
void initPolygon(){
	int n, x, y;
	// cout<<"Enter number of vertices : ";
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x>>y;
		subjectPolygon.push_back(Point(x, y));
	}
}
void drawPolygon()
{
       glColor3f(1.0, 0.0, 0.0);
       glBegin(GL_POLYGON);
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
	// cout<<"curcolor : "<<color[0]<<"	:	"<<color[1]<<"	:	"<<color[2]<<"	:	"<<endl;
	// cout<<"oldcolor : "<<oldcolor[0]<<"	:	"<<oldcolor[1]<<"	:	"<<oldcolor[2]<<"	:	"<<endl;
  int isOldColor = color[0]==oldcolor[0] && (color[1])==oldcolor[1] && (color[2])==oldcolor[2] ;
	int notNewColor = (color[0]!=newcolor[0]) || (color[1]!=newcolor[1]) || (color[2]!=newcolor[2]) ;
	return isOldColor;
}

// Flood-fill (node, target-color, replacement-color):
//  1. Set Q to the empty queue.
//  2. If the color of node is not equal to target-color, return.
//  3. Add node to the end of Q.
//  4. For each element n of Q:
//  5.  Set w and e equal to n.
//  6.  Move w to the west until the color of the node to the west of w no longer matches target-color.
//  7.  Move e to the east until the color of the node to the east of e no longer matches target-color.
//  8.  Set the color of nodes between w and e to replacement-color.
//  9.  For each node n between w and e:
// 10.   If the color of the node to the north of n is target-color, add that node to the end of Q.
//       If the color of the node to the south of n is target-color, add that node to the end of Q.
// 11. Continue looping until Q is exhausted.
// 12. Return.

void floodFill(Point seed,float oldcolor[3],float newcolor[3])
{
      queue<Point> Q;
			if(!checkPoint(seed,oldcolor,newcolor))
				return;
			Q.push(seed);
			while(!Q.empty()){
				seed = Q.front();
				Q.pop();
				Point west = seed;
				Point east = seed;
				while(checkPoint(west,oldcolor,newcolor))
					west = Point(west.x-1, west.y);
				while(checkPoint(east,oldcolor,newcolor))
					east = Point(east.x+1, east.y);
				for(int i = west.x+1;i<=east.x;i++){
					setPixel(i, seed.y, newcolor);
					Point north(i, seed.y+1);
					Point south(i, seed.y-1);
					// if(checkPoint(north,oldcolor,newcolor))
						Q.push(north);
					// if(checkPoint(south,oldcolor,newcolor))
						Q.push(south);
				}
			}
}
void mouse(int btn, int state, int x, int y)
{
       if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
          floodFill(Point(x, wh-y),intCol,fillCol);
}
void myinit()
{
      glViewport(0,0,ww,wh);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
      glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
       glutInit(&argc,argv);
       glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
       glutInitWindowSize(ww,wh);
       glutCreateWindow("Flood-Fill-Recursive");
			 initPolygon();
       glutDisplayFunc(display);
       myinit();
       glutMouseFunc(mouse);
       glutMainLoop();
       return 0;
}
