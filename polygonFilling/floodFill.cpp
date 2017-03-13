#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <queue>
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
int ww = 600, wh = 500;
float bgCol[3] = {0.0, 0.0,0.0};
float intCol[3] = {1.0,0.0,0.0};
float fillCol[3] = {0.0,0.0,1.0};
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
void drawPolygon(int x1, int y1, int x2, int y2)
{
	glColor3f(1.0,0.0,0.0);
   	glBegin(GL_LINE_LOOP);
   	glVertex2i(x1,y1);
   	glVertex2i(x1,y2);
   	glVertex2i(x2,y2);
   	glVertex2i(x2,y1);
   	glEnd();
	glFlush();
      //  glColor3f(1.0, 0.0, 0.0);
      //  glBegin(GL_POLYGON);
      //       glVertex2i(x1, y1);
      //       glVertex2i(x1, y2);
      //       glVertex2i(x2, y2);
      //       glVertex2i(x2, y1);
      //  glEnd();
      //  glFlush();
}
void display()
{
       glClearColor(0.0,0.0,0.0,1.0);
       glClear(GL_COLOR_BUFFER_BIT);
       drawPolygon(100,100,200,200);
       glFlush();
}
int checkPoint(int x , int y, float color[3], float oldcolor[3], float newcolor[3]){
  int isOldColor = color[0]==oldcolor[0] && (color[1])==oldcolor[1] && (color[2])==oldcolor[2] ;
	int notNewColor = (color[0]!=newcolor[0]) || (color[1]!=newcolor[1]) || (color[2]!=newcolor[2]) ;
	return notNewColor;
}
void floodFill8(int x,int y,float oldcolor[3],float newcolor[3])
{
      float color[3];
      getPixel(x,y,color);
			if(color[0]==oldcolor[0] && (color[1])==oldcolor[1] && (color[2])==oldcolor[2]){
				setPixel(x,y,newcolor);
				return;
			}
			if(checkPoint(x, y, color, oldcolor, newcolor)){
				setPixel(x,y,newcolor);
				floodFill8(x + 1, y    , oldcolor, newcolor);
				floodFill8(x - 1, y    , oldcolor, newcolor);
				floodFill8(x    , y + 1, oldcolor, newcolor);
				floodFill8(x    , y - 1, oldcolor, newcolor);
				// floodFill8(x + 1, y + 1, oldcolor, newcolor);
				// floodFill8(x - 1, y - 1, oldcolor, newcolor);
				// floodFill8(x - 1, y + 1, oldcolor, newcolor);
				// floodFill8(x + 1, y - 1, oldcolor, newcolor);
      }
}
int isReplacementColor(int x, int y, float oldcolor[3]){
  float color[3];
  getPixel(x,y,color);
  return ((color[0]==oldcolor[0]) && (color[1]==oldcolor[1]) && (color[2]==oldcolor[2]));
}
// void floodfill4(int x,int y,float oldcolor[3],float newcolor[3])
// {
//       float color[3];
//       getPixel(x,y,color);
//       // if((color[0]==newcolor[0]) && (color[1]==newcolor[1]) && (color[2]==newcolor[2]))
//       //   return;
//       if((color[0]!=oldcolor[0]) || (color[1]!=oldcolor[1]) || (color[2]!=oldcolor[2]))
//         return;
//       queue<Point> Q;
//       int count = 0;
//       setPixel(x,y,newcolor);
//       Q.push(Point(x, y));
//       while(!Q.empty()){
//         cout<<count++<<endl;
//         Point p = Q.front();
//         Q.pop();
//         if(isReplacementColor(p.x-1, p.y, oldcolor)){
//           setPixel(p.x-1, p.y,newcolor);
//           Q.push(Point(p.x-1, p.y));
//         }
//         if(isReplacementColor(p.x+1, p.y, oldcolor)){
//           setPixel(p.x+1, p.y, newcolor);
//           Q.push(Point(p.x+1, p.y));
//         }
//         if(isReplacementColor(p.x, p.y+1, oldcolor)){
//           setPixel(p.x, p.y+1,newcolor);
//           Q.push(Point(p.x, p.y+1));
//         }
//         if(isReplacementColor(p.x, p.y-1, oldcolor)){
//           setPixel(p.x, p.y-1,newcolor);
//           Q.push(Point(p.x, p.y-1));
//         }
//       }
// }
void mouse(int btn, int state, int x, int y)
{
       if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
       {
               int xi = x;
               int yi = (wh-y);
              //  cout<<x<<"  "<<y<<endl;
               floodFill8(xi,yi,intCol,fillCol);
							 cout<<"function end"<<endl;
       }
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
       glutDisplayFunc(display);
       myinit();
       glutMouseFunc(mouse);
       glutMainLoop();
       return 0;
}
