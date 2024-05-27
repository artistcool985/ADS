#include <stdio.h>

#define MAX 30

typedef struct edge {
  int u, v, w;
} edge;

typedef struct edge_list {
  edge data[MAX];
  int n;
} edge_list;

edge_list elist;
int Graph[MAX][MAX], n;
edge_list spanlist;

void kruskalAlgo();
int find(int belongs[], int vertexno);
void applyUnion(int belongs[], int c1, int c2);
void sort();
void print();

void kruskalAlgo() {
  int belongs[MAX], i, j, cno1, cno2;
  elist.n = 0;
  for (i = 1; i < n; i++)
    for (j = 0; j < i; j++) {
      if (Graph[i][j]!= 0) {
        elist.data[elist.n].u = i;
        elist.data[elist.n].v = j;
        elist.data[elist.n].w = Graph[i][j];
        elist.n++;
      }
    }
  sort();
  for (i = 0; i < n; i++)
    belongs[i] = i;
  spanlist.n = 0;
  for (i = 0; i < elist.n; i++) {
    cno1 = find(belongs, elist.data[i].u);
    cno2 = find(belongs, elist.data[i].v);

    if (cno1!= cno2) {
      spanlist.data[spanlist.n] = elist.data[i];
      spanlist.n = spanlist.n + 1;
      applyUnion(belongs, cno1, cno2);
    }
  }
}

int find(int belongs[], int vertexno) {
  return (belongs[vertexno]);
}

void applyUnion(int belongs[], int c1, int c2) {
  int i;
  for (i = 0; i < n; i++)
    if (belongs[i] == c2)
      belongs[i] = c1;
}

void sort() {
  int i, j;
  edge temp;
  for (i = 1; i < elist.n; i++)
    for (j = 0; j < elist.n - 1; j++)
      if (elist.data[j].w > elist.data[j + 1].w) {
        temp = elist.data[j];
        elist.data[j] = elist.data[j + 1];
        elist.data[j + 1] = temp;
      }
}

void print() {
  int i, cost = 0;
  for (i = 0; i < spanlist.n; i++) {
    printf("\n%d - %d : %d", spanlist.data[i].u, spanlist.data[i].v, spanlist.data[i].w);
    cost = cost + spanlist.data[i].w;
  }
  printf("\nSpanning tree cost: %d", cost);
}

int main() {
  n = 6;

  edge e1 = {0, 1, 4};
  edge e2 = {0, 2, 4};
  edge e3 = {1, 2, 2};
  edge e4 = {2, 3, 3};
  edge e5 = {2, 4, 4};
  edge e6 = {3, 4, 3};
  edge e7 = {4, 5, 3};
  edge e8 = {5, 2, 2};

  elist.n = 8;
  elist.data[0] = e1;
  elist.data[1] = e2;
  elist.data[2] = e3;
  elist.data[3] = e4;
  elist.data[4] = e5;
  elist.data[5] = e6;
  elist.data[6] = e7;
  elist.data[7] = e8;

  // Initialize Graph array
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      Graph[i][j] = 0;
    }
  }

  Graph[0][1] = 4;
  Graph[0][2] = 4;
  Graph[1][2] = 2;
  Graph[2][3] = 3;
  Graph[2][4] = 4;
  Graph[3][4] = 3;
  Graph[4][5] = 3;
  Graph[5][2] = 2;

  kruskalAlgo();
  print();

  return 0;
}