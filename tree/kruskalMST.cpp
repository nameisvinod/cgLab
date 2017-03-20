#include "iostream"
#include "vector"
#include "algorithm"
#include "queue"
#define true 1
#define false 0
using namespace std;
typedef  pair<int, int> iPair;
class DisjointSets
{
    int *parent, *rnk;
    int n;
  public:
    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
class Graph{
    int V, E;
    vector< pair<int, iPair> > edges;
  public:
    Graph(int V, int E)    {
        this->V = V;
        this->E = E;
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
    int kruskalMST(){
      int mst_wt = 0; // Initialize result

      sort(edges.begin(), edges.end());

      DisjointSets ds(V);

      vector< pair<int, iPair> >::iterator it;
      for (it=edges.begin(); it!=edges.end(); it++)
      {
          int u = it->second.first;
          int v = it->second.second;

          int set_u = ds.find(u);
          int set_v = ds.find(v);

          if (set_u != set_v)
          {
              cout << u << " - " << v << endl;
              mst_wt += it->first;
              ds.merge(set_u, set_v);
            }
          }
          return mst_wt;
        }
};
int main(int argc, char const *argv[]) {
  // vertices and edges count
  int V, E;
  cin>>V>>E;
  Graph g(V, E);
  for (int i = 0; i < E; i++) {
      int x, y, w;
      cin>>x>>y>>w;
      g.addEdge(x, y, w);
  }
  cout << "Edges of MST are \n";
  int mst_wt = g.kruskalMST();

  cout << "\nWeight of MST is " << mst_wt<<endl;
  return 0;
}
