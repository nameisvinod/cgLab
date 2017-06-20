#include "iostream"
#include "stdlib.h"
#include "limits.h"
#include "unistd.h"
#include "string.h"
#include "math.h"
#include "vector"
#include "algorithm"
#include <GL/glut.h>
#include <unistd.h>
#include "utility"
#define PI 3.14
using namespace std;
void drawCharacter(int , int , int);
typedef pair<int, int> iPair;
float initCol[3] = {1, 1, 1};
float finalCol[3] = {0, 1, 0};
void drawLine(int x1, int y1, int x2, int y2, float color[3]){
	glColor3fv(color);
	glBegin(GL_LINES);
		glVertex2d(x1, y1);
		glVertex2d(x2, y2);
	glEnd();
	glFlush();
}
void drawCircle(int xc, int yc, float r, float angle, float color[3]){
  int theta = angle;
  theta%=360;
  int end = theta;
  glColor3fv(color);
  glBegin(GL_LINES);
  for (; theta < 360+end; theta+=1) {
    glVertex2f(xc, yc);
    float t = theta*PI/180;
    glVertex2f(xc+r*cos(t), yc+r*sin(t));
  }
  glEnd();
  glFlush();
}
class DisjointSets
{
	int n, *parent, *rank;
public:
	DisjointSets();
	DisjointSets(int n){
		this->n = n;
		parent = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; ++i){
			parent[i] = i;
			rank[i] = 0;
		}
	}
	int find(int u){
		if(parent[u]!=u)
			parent[u]=find(parent[u]);
		return parent[u];
	}
	void merge(int x, int y){
		x = find(x);
		y = find(y);
		if(rank[x]<rank[y])
			parent[x] = y;
		else
			parent[y] = x;
		if(rank[x]==rank[y])
			rank[y]++;
	}	
};

class Graph
{
public:
	int V, E;
	vector<pair<int,iPair> > edges;
	vector<int> xCoords, yCoords;
	Graph(){};
	Graph(int V, int E){
		this->V = V;
		this->E = E;
	}
	void addEdge(int u,int v, int w){
		edges.push_back({w, {u, v}});
	}
	void addCoords(int x, int y){
		xCoords.push_back(x);
		yCoords.push_back(y);
	}
	int KrushkalMST(){
		int w = 0;
		sort(edges.begin(), edges.end());
		DisjointSets ds(V);
		vector<pair<int,iPair> >::iterator it;
		for(it= edges.begin();it!=edges.end();it++){
			int u = (it)->second.first;
			int v = (it)->second.second;
			
			int set_u = ds.find(u);
			int set_v = ds.find(v);
			if(set_u!=set_v){
				cout<<u<< "-" <<v<<endl;
				usleep(1000*1000);
				drawCircle(xCoords[u-1], yCoords[u-1], 10, 0, finalCol);
				drawCircle(xCoords[v-1], yCoords[v-1], 10, 0, finalCol);
				drawLine(xCoords[u-1], yCoords[u-1], xCoords[v-1], yCoords[v-1], finalCol);
				w+= it->first;
				ds.merge(set_u, set_v);
			}
		}
		return w;
	}
	void drawEdges(){
		vector<pair<int,iPair> >::iterator it;
		for(it= edges.begin();it!=edges.end();it++){
			int u = (it)->second.first;
			int v = (it)->second.second;
			int w = it->first;
			drawLine(xCoords[u-1], yCoords[u-1], xCoords[v-1], yCoords[v-1], initCol);
			drawCharacter(w, u, v);
		}
	}
	void drawNodes(){
		for (int i = 0; i < V; ++i)
			drawCircle(xCoords[i], yCoords[i], 10, 0, initCol);
	}
	void drawGraph(){
		drawEdges();
		drawNodes();
	}
};
Graph g;
void drawCharacter(int w, int u, int v){
	float mx = (g.xCoords[u-1] + g.xCoords[v-1])/2;
	float my = (g.yCoords[u-1] + g.yCoords[v-1])/2;
	char c = '0'+ w;
	glRasterPos3f(mx, my,0.0f);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
}
void initGraph(){
	int V, E;
	cin>>V>>E;
	g = Graph(V, E);
	int u, v, w;
	for (int i = 0; i < V; ++i){
		cin>>u>>v;
		g.addCoords(u, v);
	}
	for (int i = 0; i < E; ++i)
	{
		cin>>u>>v>>w;
		g.addEdge(u, v, w);
	}
	for (int i = 0; i < V; ++i)
	{
		cout<<g.xCoords[i]<<"		"<<g.yCoords[i]<<endl;
	}
}
void display(){
	g.drawGraph();
	cout<<g.KrushkalMST()<<endl;
}
void init(){
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(800,600);
  glutCreateWindow("Display");
  glClearColor(0.0,0.0,0.0,1.0);
  gluOrtho2D(0 , 800 , 0 , 600);
  glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char *argv[])
{
	initGraph();
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}