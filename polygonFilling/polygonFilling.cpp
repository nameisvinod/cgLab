#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int x1,Y1,x2,y2;
void seedfill(int,int,int,int);
void square(void);
void Axes(void);
void display(void)
 {
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 square();
 glEnd();
 glFlush();
 }
void square(void)
{
 seedfill(x1 , Y1 , 0 , 0);
 Axes();
} 
void seedfill(int x , int y , int flagx , int flagy)
{

 if(x<x2 && y<y2)
 {
 if(flagx==0 && flagy==0)
 {
 seedfill(x+1,y,1,0);
 seedfill(x,y+1,0,1);
 }
 if(flagx==1 && flagy ==0)
 {
 seedfill(x+1,y,1,0);
 seedfill(x,y+1,0,1);

 }
 if(flagx==0 && flagy ==1)
 {
 seedfill(x,y+1,0,1);
 }
 glVertex2s(x,y);
 } 
}

 void Axes(void)
{
 int i;
 glColor3f (1.0, 1.0, 1.0);
 for(i=-100 ; i<=100 ; i++)
 {
 glVertex2s(i,0);
 glVertex2s(0,i);
 }
 for(i=-2; i<=2 ; i++)
 {
 glVertex2s(95+i,4+i);
 glVertex2s(95-i,4+i);
 } 
 for(i=0; i<=2 ; i++)
 {
 glVertex2s(4+i,95+i);
 glVertex2s(4-i,95+i);
 glVertex2s(4,95-i);
 }
}
 void init(void)
 {
 glClearColor (0.0, 0.0, 0.0, 0.0);
 glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
 }
int main(int argc, char** argv)
{
 cout<<"Enter the bottom left co-ordinates of rectangle:\n";
 scanf("%d %d",&x1,&Y1);
 cout<<"Enter the top right co-ordinates of rectangle:\n";
 scanf("%d %d",&x2,&y2);
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize (500, 500);
 glutInitWindowPosition (100, 100);
 glutCreateWindow ("Square : Seed Fill Method ");
 init ();
 glutDisplayFunc(display);
 glutMainLoop(); 
 return 0;
}