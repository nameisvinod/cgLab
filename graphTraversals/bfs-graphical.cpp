#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
#include "vector"
#include "algorithm"
#include "queue"
#define max 2147483647
#define PI 3.14159
using namespace std;
float initColor[3] = {1, 1, 1};
float inStackColor[3] = {.5, 0.5, 0.5};
float processedColor[3] = {0, 1, 0};
float processedLineColor[3] = {0, 1, 1};
const float DEG2RAD = 3.14159/180, radius = 20;
void drawFilledCircle(float, float, float, float[]);
void drawLine(int, int , int, int, float[]);
void drawBitmapText(char *,float,float);
//Logic
class Graph{
    int V, E;
    vector<vector<int> > adj;
    vector<int> dist,xCoords, yCoords;
  public:
    Graph(int V, int E){
        this->V = V;
        this->E = E;
        adj = vector<vector<int> >(V, vector<int>());
        dist = vector<int>(V);
    }
    void addEdge(int u, int v)
    {
      adj[u - 1].push_back(v);
      adj[v - 1].push_back(u);
    }
    void addCoords(int x, int y){
      xCoords.push_back(x);
      yCoords.push_back(y);
    }
    void print(){
      for (int i = 0; i < xCoords.size(); i++) {
        cout<< i+1 << " --->"<< xCoords[i] <<"  "<< yCoords[i]<< endl;
      }
      for(int i=0;i<adj.size();i++){
        cout<< i+1 << "-----> ";
        for(int j=0;j<adj[i].size();j++)
          cout<<adj[i][j]<<"  ";
        cout<<endl;
      }
    }
    void bfs(int n){
        for(int i=0;i<V;i++)
          dist[i] = max;
        dist[n-1] = 0;
        usleep(1000 * 1000); // takes microseconds
        drawFilledCircle(radius-1,xCoords[n-1] ,yCoords[n-1], inStackColor);
        queue<int> Q;
        Q.push(n);
        while(!Q.empty()){
          int m = Q.front();
          usleep(1000 * 1000); // takes microseconds
          drawFilledCircle(radius-1,xCoords[m-1] ,yCoords[m-1], processedColor);
          Q.pop();
          for (int i=0;i<adj[m-1].size();i++) {
            int o = adj[m-1][i];
            if(dist[o-1]==max){
              usleep(1000 * 1000); // takes microseconds
              drawLine(xCoords[m-1], yCoords[m-1], xCoords[o-1], yCoords[o-1], processedLineColor);
              dist[o-1] = dist[m-1] + 1;
              Q.push(o);
            }
          }
        }
    }
    int distance(int x, int y){
        bfs(x);
        int d = dist[y-1];
        return d==max ? -1 : d;
    }
    void drawNodes(){
      for (int i = 0; i < xCoords.size(); i++){
        // drawHollowCircle(radius,xCoords[i] ,yCoords[i]);
        drawFilledCircle(radius-1,xCoords[i] ,yCoords[i], initColor);
      }
    }
    void drawEdges(){
      for(int i=0;i<adj.size();i++){
        for(int j=0;j<adj[i].size();j++){
          int to = adj[i][j]-1;
          drawLine(xCoords[i], yCoords[i], xCoords[to], yCoords[to], inStackColor);
        }
      }
    }
    void drawGraph(){
      drawEdges();
      drawNodes();
    }
    //for coloring nodes over the lines
    void clear(){
      for (int i = 0; i < xCoords.size(); i++)
        drawFilledCircle(radius-1,xCoords[i] ,yCoords[i], processedColor);
    }
};
//graphical
void drawLine(int x1, int y1, int x2, int y2, float color[3]){
  glColor3fv(color);
  glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
  glEnd();
  glFlush();
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
void drawBitmapText(char *string,float x,float y){
	char *c;
	glRasterPos2f(x, y);
  glColor3f(0 ,1, 0);
	for (c=string; *c != '\0'; c++){
    cout<<*c<<endl;
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
  }
}

void BFS(void){
  int V, E, start , goal;
  int x, y;
  cin>>V>>E;
  Graph g(V, E);
  for (int i = 0; i < V; i++) {
    cin>>x>>y;
    g.addCoords(x, y);
  }
  for (int i = 0; i < E; i++) {
    cin>>x>>y;
    g.addEdge(x, y);
  }
  cin>>start>>goal;
  g.drawGraph();
  // g.print();
  cout<<"Distance : "<< g.distance(start, goal)<<endl;
  g.clear();
}
void Init()
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("BFS Traversal");
  glClearColor(0.0,0.0,0.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}
int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  Init();
  glutDisplayFunc(BFS);
  glutMainLoop();
  return 0;
}
