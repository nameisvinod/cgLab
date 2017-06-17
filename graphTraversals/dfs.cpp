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
    void explore(int n) {
        // cout<<n<<endl;
        // usleep(1000 * 1000); // takes microseconds
        // drawFilledCircle(radius-1,xCoords[n-1] ,yCoords[n-1], inStackColor);
        for (int i=0;i<adj[n-1].size();i++) {
            int o = adj[n-1][i];
            if(dist[o-1]==max){
              dist[o-1] = dist[n-1] + 1;
              explore(o);
            }
        }
        // usleep(1000 * 1000); // takes microseconds
        // drawFilledCircle(radius-1,xCoords[n-1] ,yCoords[n-1], processedColor);
    }
    void dfs(int n){
      for(int i=0;i<V;i++)
        dist[i] = max;
      dist[n-1] = 0;
      explore(n);
    }
    int distance(int x, int y){
        dfs(x);
        int d = dist[y-1];
        return d==max ? -1 : d;
    }
};
int main(int argc, char const *argv[]) {
  // vertices and edges count
  int V, E, start , goal;
  cin>>V>>E;
  Graph g(V, E);
  for (int i = 0; i < E; i++) {
      int x, y;
      cin>>x>>y;
      g.addEdge(x, y);
  }
  cin>>start>>goal;
  // g.print();
  cout<<"Distance : "<< g.distance(start, goal)<<endl;
  return 0;
}
