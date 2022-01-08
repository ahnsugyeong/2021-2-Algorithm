/*
 * 인접행렬 구조를 사용하였다.
 * 실습에서 했던 BFS를 그대로 했으며
 * 인접행렬을 방문하면서 그 행렬의 간선의 e_visit이 2가 나오면(cross 간선)
 * 해당 간선의 정점의 이름들을 출력해주었다.
 * 추가로 한번더 출력하는 걸 막기 위하여 e_visit을 3으로 바꿔주었다.
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    int name;
    int v_visit;
}Vertex;

typedef struct Edge{
    struct Vertex* origin;
    struct Vertex* destination;
    int weight;
    int e_visit;
}Edge;

typedef struct Graph{
    struct Vertex* vertex;
    struct Edge* edge;
}Graph;

void initGraph(Graph *g, int n, int m){
    g->vertex = (Vertex*)malloc(sizeof(Vertex)*n);
    g->edge = (Edge*)malloc(sizeof(Edge)*m);

    for(int i=0;i<n;i++){
        g->vertex[i].name = i+1;
    }
}

void insertVE(Graph* g, Edge*** M, int name1, int name2, int w){
    Vertex* v1 = &(g->vertex[name1-1]);
    Vertex* v2 = &(g->vertex[name2-1]);
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->weight = w;
    new_edge->origin = v1;
    new_edge->destination = v2;

    M[name1-1][name2-1] = new_edge;
    if(name1 != name2) M[name2-1][name1-1] = new_edge;

}

void BFS(Graph* g, Edge*** M, int name, int n){
    int sum = 0;
    int* queue = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        queue[i] = 0;
    }
    queue[0] = name;
    int last = 1;

    while(queue[0]!=0) {
        name = queue[0];
        int index = name - 1;

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
                        sum += M[index][i]->weight;

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
                        sum += M[index][i]->weight;
                    }
                    else {
                        M[index][i]->e_visit = 2;
                    }
                }
            }
            if(M[index][i]->e_visit == 2){
                printf("%d %d\n", M[index][i]->origin->name, M[index][i]->destination->name);
                M[index][i]->e_visit = 3;
            }

        }
    }

    printf("%d\n", sum);

}
int main(){
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    Graph g;
    initGraph(&g, n, m);
    Edge*** M = (Edge***)malloc(sizeof(Edge**)*n);
    for(int i=0;i<n;i++) {
        M[i] = (Edge**)malloc(sizeof(Edge*)*n);
        for(int j=0;j<n;j++) M[i][j] = NULL;
    }

    int name1, name2, w;
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &name1, &name2, &w);
        insertVE(&g, M, name1, name2, w);
    }

    BFS(&g, M, s, n);
    return 0;
}
