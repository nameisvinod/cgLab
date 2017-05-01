// polygon Clipping using Sutherland-Hodgeman Algorithm
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;
float xmin=220;
float ymin=220;
float xmax=420;
float ymax=420;
const int TOP = 8, BOTTOM = 4, LEFT = 2, RIGHT = 1;
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
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0,0.0);
	glBegin(GL_POLYGON);
	for (Point point : subjectPolygon)
		glVertex2i(point.x,point.y);
	glEnd();

	glColor3f(0.0,1.0,0.0);
   	glBegin(GL_LINE_LOOP);
   	glVertex2i(xmin,ymin);
   	glVertex2i(xmin,ymax);
   	glVertex2i(xmax,ymax);
   	glVertex2i(xmax,ymin);
   	glEnd();
	glFlush();
}
Point computeIntersection(Point S,Point E, int clipEdge){
	float m1 = (E.y-S.y)/(E.x-S.x);
	float b1, x, y;
	switch(clipEdge){
		case LEFT:
			if(m1==0)
				return Point(xmin, E.y);
			b1 = E.y - m1*E.x;
			y = m1*xmin + b1;
			return Point(xmin, y);
			break;
		case TOP:
			if((E.x-S.x) == 0)
				return Point(E.x, ymax);
			b1 = E.y - m1*E.x;
			x = (ymax - b1)/m1 ;
			return Point(x, ymax);
			break;
		case RIGHT:
			if(m1==0)
				return Point(xmax, E.y);
			b1 = E.y - m1*E.x;
			y = m1*xmax + b1;
			return Point(xmax, y);
			break;
		case BOTTOM:
			if((E.x-S.x) == 0)
				return Point(E.x, ymin);
			b1 = E.y - m1*E.x;
			x = (ymin - b1)/m1 ;
			return Point(x, ymin);
			break;
	}
}
list<Point> clipLeft(list<Point> outputList){
	list<Point> inputList = outputList;
	outputList.clear();
	Point S = inputList.back();
	for(Point E : inputList){
		//E inside clipEdge
		if(E.x>xmin){
			// S not inside clipEdge
			if(S.x < xmin)
				outputList.push_back(computeIntersection(S,E,LEFT));
			outputList.push_back(E);
		}
		// S inside clipEdge
		else if(S.x > xmin)
			outputList.push_back(computeIntersection(S,E,LEFT));
		S = E;
	}
	return outputList;
}
list<Point> clipRight(list<Point> outputList){
	list<Point> inputList = outputList;
	outputList.clear();
	Point S = inputList.back();
	for(Point E : inputList){
		//E inside clipEdge
		if(E.x<xmax){
			// S not inside clipEdge
			if(S.x > xmax)
				outputList.push_back(computeIntersection(S,E,RIGHT));
			outputList.push_back(E);
		}
		// S inside clipEdge
		else if(S.x < xmax)
			outputList.push_back(computeIntersection(S,E,RIGHT));
		S = E;
	}
	return outputList;
}
list<Point> clipTop(list<Point> outputList){
	list<Point> inputList = outputList;
	outputList.clear();
	Point S = inputList.back();
	for(Point E : inputList){
		//E inside clipEdge
		if(E.y<ymax){
			// S not inside clipEdge
			if(S.y > ymax)
				outputList.push_back(computeIntersection(S,E,TOP));
			outputList.push_back(E);
		}
		// S inside clipEdge
		else if(S.y < ymax)
			outputList.push_back(computeIntersection(S,E,TOP));
		S = E;
	}
	return outputList;
}
list<Point> clipBottom(list<Point> outputList){
	list<Point> inputList = outputList;
	outputList.clear();
	Point S = inputList.back();
	for(Point E : inputList){
		//E inside clipEdge
		if(E.y>ymin){
			// S not inside clipEdge
			if(S.y < ymin)
				outputList.push_back(computeIntersection(S,E,BOTTOM));
			outputList.push_back(E);
		}
		// S inside clipEdge
		else if(S.y > ymin)
			outputList.push_back(computeIntersection(S,E,BOTTOM));
		S = E;
	}
	return outputList;
}
// fro debugging
void print(list<Point> outputList){
	for(Point E : outputList){
		cout<< E.x <<"	"<<E.y<<endl;
	}
}
void initializePolygon(){
	// polygon to be clipped
	subjectPolygon.push_back(Point(300,100));
	subjectPolygon.push_back(Point(100,800));
	subjectPolygon.push_back(Point(400,300));
	subjectPolygon.push_back(Point(600,150));
	subjectPolygon.push_back(Point(400,100));
}
void sutherland_Hodgeman()
{
	std::list<Point> outputList = subjectPolygon;
	outputList = clipLeft(outputList);
	outputList = clipTop(outputList);
	outputList = clipRight(outputList);
	outputList = clipBottom(outputList);
	subjectPolygon = outputList;
	display();
}
void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  cout<<"Hello";
        sutherland_Hodgeman();
        glFlush();
    }
}
void init(void) {
	glClearColor(0,0,0,0);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glutDisplayFunc(display);
    glutKeyboardFunc(mykey);

	glLoadIdentity();
	gluOrtho2D(0 , 640 , 0 , 640);
}
int main(int argc,char * argv[]) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sutherland Hodgeman Polygon Clipping");
	//initialise polygon coordinates
	initializePolygon();
	init();
	glutMainLoop();
	return 0;
}
