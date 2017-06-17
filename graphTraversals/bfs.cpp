#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"
#define max 2147483647
#define true 1
#define false 0
using namespace std;
typedef int Boolean;
class Graph{
    int V, E;
    vector<vector<int> > adj;
    vector<int> dist;
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
    void print(){
      
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
        queue<int> Q ;
        Q.push(n);
        while(!Q.empty()){
          int m = Q.front();
          Q.pop();
          for (int i=0;i<adj[m-1].size();i++) {
            int o = adj[m-1][i];
            if(dist[o-1]==max){
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
};
int main(int argc, char const *argv[]) {
  // vertices and edges count
  int V, E, start , goal;
  int x, y;
  cin>>V>>E;
  // cout<<V<<E<<endl;
  Graph g(V, E);
  for (int i = 0; i < E; i++) {
    cin>>x>>y;
    g.addEdge(x, y);
  }
  cin>>start>>goal;
  // g.print();
  cout<<"Distance : "<< g.distance(start, goal)<<endl;
  return 0;
}
