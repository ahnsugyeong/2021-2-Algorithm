#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    int v_visit;
    int name;
}Vertex;

typedef struct Edge{
    int e_visit;
    struct Vertex* origin;
    struct Vertex* destination;
}Edge;

typedef struct Graph{
    struct Vertex* vertex;
    struct Edge* edge;
}Graph;

void initGraph(Graph* g, int n, int m){
    g->vertex = (Vertex*)malloc(sizeof(Vertex)*n);
    g->edge = (Edge*)malloc(sizeof(Edge)*m);

    for(int i=0;i<n;i++){
        g->vertex[i].name = i+1;
    }
}
void insertVEA(Graph* g, Edge*** M, int name1, int name2){
    Vertex* v1 = &(g->vertex[name1-1]);
    Vertex* v2 = &(g->vertex[name2-1]);

    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->origin = v1;
    new_edge->destination = v2;
    M[name1-1][name2-1] = new_edge;

    if(name1!=name2) M[name2-1][name1-1] = new_edge;

}
/*
 * v_visit
 * 0: 방문 안 한 정점
 * 1: 방문 한 정점
 *
 * e_visit
 * 0: 방문 안 한 간선
 * 1: 방문 한 간선 (tree 간선)
 * 2: cross 간선
 */
void BFS(Graph* g, Edge*** M, int name, int n){

    int* queue = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        queue[i] = 0;
    }
    queue[0] = name;
    int last = 1;

    while(queue[0]!=0) {

        name = queue[0];
        int index = name - 1;

        printf("%d\n", name);

        for (int i = 0; i < last; i++) {
            queue[i] = queue[i + 1];
        }
        last--;

        for (int i = 0; i < n; i++) {
            if (M[index][i] == NULL) continue;

            //간선 방문한 적 없으면
            if (M[index][i]->e_visit == 0) {
                if (M[index][i]->origin->name == name) {
                    if (M[index][i]->destination->v_visit == 0) {
                        queue[last] = i + 1;
                        last++;
                        M[index][i]->e_visit = 1;
                        M[index][i]->destination->v_visit = 1;

                    }
                    else {
                        M[index][i]->e_visit = 2;
                    }
                }
                else {
                    if (M[index][i]->origin->v_visit == 0) {
                        queue[last] = i + 1;
                        last++;
                        M[index][i]->e_visit = 1;

                        M[index][i]->origin->v_visit = 1;
                    }
                    else {
                        M[index][i]->e_visit = 2;
                    }
                }
            }

        }
    }



}

int main(){
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    Graph g;
    initGraph(&g, n, m);

    Edge*** M = (Edge***)malloc(sizeof(Edge**)*n);
    for(int i=0;i<n;i++) {
        M[i] = (Edge*)malloc(sizeof(Edge)*n);
        for(int j=0;j<n;j++) {
            M[i][j] = NULL;
        }
    }

    int name1, name2;
    for(int i=0;i<m;i++){
        scanf("%d %d", &name1, &name2);
        insertVEA(&g, M, name1, name2);
    }

    BFS(&g, M, s, n);


}
/*
6 9 1
3 5
1 3
4 1
2 3
3 4
6 4
3 6
1 2
2 5

8 12 4
1 2
2 4
4 7
3 6
6 1
7 6
7 8
1 3
2 7
1 4
2 5
7 5
 */