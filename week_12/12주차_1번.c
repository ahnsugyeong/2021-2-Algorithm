#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    int inDegree;
    char name;
    struct AdjList* adj;
}Vertex;

typedef struct Edge{
    struct Vertex* origin;
    struct Vertex* destination;
}Edge;

typedef struct AdjList{
    struct Edge* edge;
    struct AdjList* next;
}AdjList;

typedef struct Graph{
    struct Vertex* vertex;
    struct Edge* edge;
}Graph;

int index(Graph* g, int n, char name){
    for(int i=0;i<n;i++){
        if(g->vertex[i].name == name) return i;
    }
}

void insertVEA(Graph* g, int n, char name1, char name2){
    Vertex* o = &(g->vertex[index(g, n, name1)]);
    Vertex* d = &(g->vertex[index(g, n, name2)]);

    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->origin = o;
    new_edge->destination = d;
    new_edge->destination->inDegree ++;

    AdjList* new_adj = (AdjList*)malloc(sizeof(AdjList));
    new_adj->edge = new_edge;
    new_adj->next = o->adj->next;
    o->adj->next = new_adj;

}

void insertVertex(Graph* g, int n){
    g->vertex = (Vertex*)malloc(sizeof(Vertex)*n);
    for(int i=0;i<n;i++){
        getchar();
        scanf("%c", &g->vertex[i].name);
        g->vertex[i].adj = (AdjList*)malloc(sizeof(AdjList));
        g->vertex[i].adj->next = NULL;
    }
}
void insertDirectedEdge(Graph* g, int n, int m){
    g->edge = (Edge*)malloc(sizeof(Edge)*m);
    char name1, name2;
    for(int i=0;i<m;i++){
        scanf("%c %c", &name1, &name2);
        getchar();
        insertVEA(g, n, name1, name2);
    }
}
int topologicalSort(Graph* g, int n, int* topSort){
    int* queue = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) queue[i] = -1;
    int last = 0;

    for(int i=0;i<n;i++){
        if(g->vertex[i].inDegree == 0) {
            queue[last] = i;
            last++;
        }
    }


    int top = 0;

    while(queue[0]!=-1){
        //printf("queue[0] = %d\n", queue[0]);
        topSort[top] = queue[0];
        top++;

        for(int i=0;i<last;i++){
            queue[i] = queue[i+1];
        }
        last--;

        AdjList* tmp = g->vertex[topSort[top-1]].adj->next;
        while(tmp != NULL){
            tmp->edge->destination->inDegree--;
            if(tmp->edge->destination->inDegree == 0){
                queue[last] = index(g, n, tmp->edge->destination->name);
                last++;
            }
            tmp = tmp->next;
        }
    }
    if(top<n) return 0;
    else return 1;
}

int main(){
    int n, m;
    scanf("%d", &n);
    Graph g;
    insertVertex(&g, n);

    getchar();
    scanf("%d", &m);
    getchar();
    insertDirectedEdge(&g, n, m);

    int* topSort = (int*)malloc(sizeof(int)*n);
    int tmp = topologicalSort(&g, n, topSort);
    if(tmp == 0) printf("0\n");
    else{
        for(int i=0;i<n;i++){
            printf("%c ", g.vertex[topSort[i]].name);
        }
    }


    return 0;
}
/*
3
A B C
3
A B
C A
C B
 */