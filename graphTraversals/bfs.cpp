#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"
#define max 2147483647
#define true 1
#define false 0
using namespace std;
typedef int Boolean;
class Node{
public:
        vector<int> adj;
        int value;
        int dist;
        Boolean visited = false;
        Node(int value){
            this->value = value;
            this->dist = max;
        }
        Boolean isVisited(){
            return visited;
        }
        void setVisited(){
            visited = true;
        }
        void setDistance(int d){
            dist = d;
        }
        int getDistance(){
            return dist;
        }
    };
    bool operator==(Node &n1, const Node &n2){return n1.value == n2.value;}
    class Graph{
    public:
        vector<Node> nodes;
        int dist;
        Graph(){
          dist = 0;
        };
        void addVertex(int v){
            nodes.push_back(Node(v));
        }
        void addEdge(int x, int y){
          nodes[x-1].adj.push_back(y);
          nodes[y-1].adj.push_back(x);
        }
        void print(){
          for(int i = 0;i<nodes.size();i++){
            cout<<nodes[i].value <<"------->";
            for(int j=0;j<nodes[i].adj.size();j++)
              cout<<nodes[i].adj[j]<<" --> ";
            cout<<endl;
          }
        }
        void bfs(Node n){
            nodes[n.value-1].setDistance(0);
            queue<Node> Q ;
            Q.push(nodes[n.value-1]);
            while(!Q.empty()){
              Node m = Q.front();
              Q.pop();
              for (int i=0;i<m.adj.size();i++) {
                Node o = nodes[m.adj[i]-1];
                if(o.getDistance()==max){
                  nodes[m.adj[i]-1].setDistance(m.getDistance()+1);
                  Q.push(nodes[m.adj[i]-1]);
                }
              }
            }
        }
        int distance(int x, int y){
            Node n = nodes[x-1];
            bfs(n);
            int dist = nodes[y-1].getDistance();
            return dist==max ? -1 : dist;
        }
    };
int main(int argc, char const *argv[]) {
  // vertices and edges count
  int n, m, start , goal;
  cin>>n>>m;
  Graph graph = Graph();
  for (int i = 0; i < n; i++) {
      graph.addVertex(i+1);
  }
  for (int i = 0; i < m; i++) {
      int x, y;
      cin>>x>>y;
      graph.addEdge(x, y);
  }
  cin>>start>>goal;
  cout<<"Distance : "<< graph.distance(start, goal)<<endl;
  return 0;
}
