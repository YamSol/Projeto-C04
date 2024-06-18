#include<iostream>
#include<list>
using namespace std;

#define INT_MAX 99999

struct edge{
	int orig;
	int dest;
	int weigth;
};

int shortest_path_dijkstra(list<edge> adj[], int vertices, int start, int end) {
  bool intree[vertices];
  int distance[vertices], parent[vertices];

  for (int u = 0; u < vertices; u++) {
    intree[u] = false;
    distance[u] = INT_MAX;
    parent[u] = -1;
  }
  distance[start] = 0;
  int v = start;
  while (intree[v] == false) {
    intree[v] = true;
    list<edge>::iterator p;
    for (p = adj[v].begin(); p != adj[v].end(); p++) {
      int dest = p->dest;
      int weight = p->weigth;
      if (distance[dest] > distance[v] + weight) {
        distance[dest] = distance[v] + weight;
        parent[dest] = v;
      }
    }
    v = 0;
    int dist = INT_MAX;
    for (int u = 0; u < vertices; u++) {
      if (intree[u] == false && dist > distance[u]) {
        dist = distance[u];
        v = u;
      }
    }
  }
  return distance[end];
}

int main(){
	
	int num_vertices, directed;
	cin >> num_vertices >> directed;
	
	list<edge>adj[num_vertices];
	
	int v1, v2, w;
	while(cin >> v1 >> v2 >> w && v1 != -1 && v2 != -1 && w != -1){
		adj[v1].push_back({v1,v2,w});
		if(directed == 0)
			adj[v2].push_back({v2,v1,w});
	}
	
	cout << shortest_path_dijkstra(adj, num_vertices, 0, 4) << endl;
	
}
/*
5 0
0 1 10
0 2 12
0 3 13
0 4 14
1 2 12
2 3 23
3 4 34
-1 -1 -1
*/
