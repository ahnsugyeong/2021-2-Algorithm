#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    int v_visit;
    int name;
    struct AdjList* adj;
}Vertex;
typedef struct Edge{
    int e_visit;
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
void initGraph(Graph* g, int n, int m){
    g->vertex = (Vertex*)malloc(sizeof(Vertex)*n);
    g->edge = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<n;i++) {
        g->vertex[i].name = i+1;
        g->vertex[i].adj = (AdjList *)malloc(sizeof(AdjList));
        g->vertex[i].adj->next = NULL;
    }
}
void insertAdjList(Vertex* v, Edge* new_edge){
    AdjList* new_adj = (AdjList*)malloc(sizeof(AdjList));
    new_adj->edge = new_edge;

    Vertex* op;
    if(new_edge->origin == v) op = new_edge->destination;
    else op = new_edge->origin;

    AdjList* tmp = v->adj;
    while(tmp->next != NULL){
        if(v == tmp->next->edge->origin){
            if(tmp->next->edge->destination->name < op->name) tmp = tmp->next;
            else break;
        }
        else{
            if(tmp->next->edge->origin->name < op->name) tmp = tmp->next;
            else break;
        }
    }
    new_adj->next = tmp->next;
    tmp->next =new_adj;
}

void insertVEA(Graph* g,int name1, int name2){
    Vertex* v1 = &(g->vertex[name1-1]);
    Vertex* v2 = &(g->vertex[name2-1]);

    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->origin = v1;
    new_edge->destination = v2;

    insertAdjList(v1, new_edge);

    if(name1!=name2){
        insertAdjList(v2, new_edge);
    }
}
/*
 * v_visit
 * 0: 방문 안 한 정점
 * 1: 방문 한 정점
 *
 * e_visit
 * 0: 방문 안 한 간선
 * 1: 방문 한 tree 간선
 * 2: 방문 안 했지만 필요 없는 back 간선
*/
void DFS(Graph* g, int name){

    int index = name-1;
    printf("%d\n", name);
    g->vertex[index].v_visit = 1;

    AdjList* tmp = g->vertex[index].adj->next;
    while(tmp != NULL){
        if(tmp->edge->e_visit == 0){
            if(g->vertex[index].name == tmp->edge->origin->name){
                if(tmp->edge->destination->v_visit == 1) {
                    //back 간선
                    tmp->edge->e_visit = 2;
                }
                else{
                    //tree 간선
                    tmp->edge->e_visit = 1;

                    //재귀적 탐색
                    DFS(g, tmp->edge->destination->name);
                }
            }
            else{
                if(tmp->edge->origin->v_visit == 1) {
                    //back 간선
                    tmp->edge->e_visit = 2;

                }
                else{
                    //tree 간선
                    tmp->edge->e_visit = 1;

                    //재귀적 탐색
                    DFS(g, tmp->edge->origin->name);
                }
            }
        }
        else{
            tmp = tmp->next;
        }
    }
    return;



}

int main(){
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    Graph g;
    initGraph(&g, n, m);
    int name1, name2;
    for(int i=0;i<m;i++){
        scanf("%d %d", &name1, &name2);
        insertVEA(&g, name1, name2);
    }

    DFS(&g, s);

}
/*
5 7 1
1 2
1 4
5 1
3 5
4 3
3 1
2 3
 */