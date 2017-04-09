#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"
#include "limits.h"
#define max INT_MAX
using namespace std;
typedef  pair<int, int> iPair;
bool sortFunction (int, int);
class Graph{
public:
    int V, E;
    vector< vector<iPair> > adj;
    vector<int> dist, prev;
    Graph(){}
    Graph(int V, int E)    {
        this->V = V;
        this->E = E;
        adj = vector<vector<iPair> >(V, vector<iPair>());
        dist = vector<int>(V);
        prev = vector<int>(V);
    }
    void addEdge(int u, int v, int w)
    {
        adj[u-1].push_back({v, w});
    }
    int dijkstra(int n){
      for (size_t i = 0; i < V; i++) {
        dist[i] = max;
        prev[i] = -1;
      }
      vector<int> queue;
      dist[n-1]=0;
      queue.push_back(n);
      std::sort (queue.begin(), queue.end(), sortFunction);
      while(queue.size()!=0) {
        int m =  queue[0];
        queue.erase(queue.begin());
        for (int i = 0; i < adj[m-1].size(); i++) {
          int o = adj[m-1][i].first;
          int w = adj[m-1][i].second;
          if(dist[o-1] > (dist[m-1] + w)){
              queue.erase(std::remove(queue.begin(), queue.end(), o), queue.end());
              dist[o-1] = dist[m-1] + w;
              prev[o-1] = m;
              queue.push_back(o);
              std::sort (queue.begin(), queue.end(), sortFunction);

          }
        }
      }
    }
    void print(){
      for (size_t i = 0; i < V; i++) {
        // cout<< i+1 << "---->" << dist[i]<<endl;
        cout<< i+1 << "---->" << prev[i]<<endl;
      }
    }
    int distance(int x, int y){
      dijkstra(x);
      return dist[y-1]==max?-1:dist[y-1];
    }
    void printPath(int x, int y){
      cout<<y;
      while(prev[y-1]!=-1){
        cout<<"------>"<<prev[y-1];
        y = prev[y-1];
      }
      cout<<endl;
    }
};
Graph g;
bool sortFunction (int i,int j) { return (g.dist[i-1]<g.dist[j-1]); }
int main(int argc, char const *argv[]) {
  // vertices and edges count
  int V, E, start, end;
  cin>>V>>E;
  g = Graph(V, E);
  for (int i = 0; i < E; i++) {
      int x, y, w;
      cin>>x>>y>>w;
      g.addEdge(x, y, w);
  }
  cin>>start>>end;
  g.dijkstra(start);
  // g.print();
  cout<<"Distance : "<< g.distance(start, end)<<endl;
  // cout<<"Path : "<<endl ;
  g.printPath(start, end);
  return 0;
}
