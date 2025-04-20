#include<iostream>

using namespace std;
class dj {
  int n, cost[10][10], d[10], p[10], v[10];
  public: void read_matrix();
  void short_path(int);
  void display(int);
};
void dj::read_matrix() {
  int i, j;
  cout << "Enter the number of vertices\n";
  cin >> n;
  cout << "Enter the cost adjacency matrix\n";
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      cin >> cost[i][j];
}
void dj::short_path(int src) {
  int i, j, min, u, s;
  for (i = 0; i < n; i++) {
    d[i] = cost[src][i];
    v[i] = 0;
    p[i] = src;
  }
  v[src] = 1;
  for (i = 0; i < n; i++) {
    min = 99;
    u = 0;
    for (j = 0; j < n; j++) {
      if (!v[j])
        if (d[j] < min) {
          min = d[j];
          u = j;
        }
    }
    v[u] = 1;
    for (s = 0; s < n; s++)
      if (!v[s] && (d[u] + cost[u][s] < d[s])) {
        d[s] = d[u] + cost[u][s];
        p[s] = u;
      }
  }
}
void dj::display(int src) {
  int i, k, parent;
  for (i = 0; i < n; i++) {
    if (i == src)
      continue;
    k = i;
    cout << k << "<----";
    while (p[k] != src) {
      cout << "The shortest path from " << src << " to " << i << " is " << endl;
      cout << p[k] << "<---";
      k = p[k];
    }
    cout << src << endl;
    cout << "and the distance is " << d[i] << endl;
  }
}
int main() {
  int source;
  dj dij;
  dij.read_matrix();
  cout << "enter the source" << endl;
  cin >> source;
  dij.short_path(source);
  dij.display(source);
  return 0;
}