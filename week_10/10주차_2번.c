#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    int name;
}Vertex;

typedef struct Edge{
    struct Vertex* origin;
    struct Vertex* destination;
    int weight;
}Edge;

typedef struct Graph{
    Vertex vertex[6];
    Edge edge[8];
}Graph;



void insertVE(Graph* g, Edge** M, int name1, int name2, int w){

    Vertex* v1 = &(g->vertex[name1-1]);
    Vertex* v2 = &(g->vertex[name2-1]);

    Edge new_edge;
    new_edge.origin = v1;
    new_edge.destination = v2;
    new_edge.weight = w;

    M[name1-1][name2-1] = new_edge;

    if(name1 != name2){
        M[name2-1][name1-1] = new_edge;
    }
}
int isEmpty(Edge e){
    if(e.origin == NULL || e.destination == NULL) return 1;
    else return 0;
}
void searchAdjVertex(Graph* g, Edge** M, int name){
    if(name<1||name>6){
        printf("-1\n");
        return;
    }
    for(int i=0;i<6;i++){
        if(!isEmpty(M[name-1][i])){
            if(M[name-1][i].origin == &(g->vertex[name-1])) printf(" %d %d", M[name-1][i].destination->name, M[name-1][i].weight);
            else printf(" %d %d", M[name-1][i].origin->name, M[name-1][i].weight);
        }
    }
    printf("\n");
}

void modifyGraph(Graph* g, Edge** M, int name1, int name2, int w){
    if(name1<1||name1>6||name2<1||name2>6){
        printf("-1\n");
        return;
    }

    if(w == 0){
        if(isEmpty(M[name1-1][name2-1])) return;
        else {
            M[name1-1][name2-1].origin = NULL;
            M[name1-1][name2-1].destination = NULL;
            M[name1-1][name2-1].weight = 0;

            if(name1 != name2){
                M[name2-1][name1-1].origin = NULL;
                M[name2-1][name1-1].destination = NULL;
                M[name2-1][name1-1].weight = 0;
            }
        }
    }
    else{
        if(isEmpty(M[name1-1][name2-1])) insertVE(g, M, name1, name2, w);
        else{
            M[name1-1][name2-1].weight = w;
            if(name1 != name2) M[name2-1][name1-1].weight = w;
        }
    }

}

int main(){
    Graph g;
    //인접 행렬 메모리 할당 및 초기화
    Edge** M = (Edge**)malloc(sizeof(Edge*)*6);
    for(int i=0;i<6;i++) {
        M[i] = (Edge *) malloc(sizeof(Edge)*6);
        for(int j=0;j<6;j++){
            M[i][j].origin = NULL;
            M[i][j].destination = NULL;
        }
        g.vertex[i].name = i+1;
    }

    insertVE(&g, M, 1, 2, 1);
    insertVE(&g, M, 1, 3, 1);
    insertVE(&g, M, 1, 4, 1);
    insertVE(&g, M, 1, 6, 2);
    insertVE(&g, M, 2, 3, 1);
    insertVE(&g, M, 3, 5, 4);
    insertVE(&g, M, 5, 5, 4);
    insertVE(&g, M, 5, 6, 3);

    char order;
    int name;
    int name1, name2, w;
    while(1){
        scanf("%c", &order);
        if(order == 'a'){
            scanf("%d", &name);
            searchAdjVertex(&g, M, name);
        }
        else if(order == 'm'){
            scanf("%d %d %d", &name1, &name2, &w);
            modifyGraph(&g, M, name1, name2, w);
        }
        else if(order == 'q'){
            break;
        }
        getchar();
    }
    return 0;
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VERTEX_NUM 6

typedef struct Vertex{
    int name;
}Vertex;

typedef struct Edge{
    struct Vertex* origin;
    struct Vertex* destination;
    int weight;
}Edge;

typedef struct Graph{
    Vertex v[VERTEX_NUM];
}Graph;

void graphInit(Graph *g, Edge** M){
    for(int i=0;i<VERTEX_NUM;i++) {
        g->v[i].name = i + 1;
    }
    for(int i=0;i<VERTEX_NUM;i++){
        for(int j = 0 ;j <VERTEX_NUM ;j++){
            M[i][j].origin = NULL;
            M[i][j].destination = NULL;
        }
    }
}
void insertVE(Graph *g, int name1, int name2, int weight, Edge** M) {

    Vertex *v1 = &(g->v[name1 - 1]);
    Vertex *v2 = &(g->v[name2 - 1]);
    Edge *e = (Edge *) malloc(sizeof(Edge));
    e->origin = v1;
    e->destination = v2;
    e->weight = weight;
    M[name1 - 1][name2 - 1] = *e;

    if (name1 != name2) {
        Edge *e2 = (Edge *) malloc(sizeof(Edge));
        e2->origin = v2;
        e2->destination = v1;
        e2->weight = weight;
        M[name2 - 1][name1 - 1] = *e2;
    }
}
void printGraph(Graph *g, int name, Edge** M) {
    if (name < 1 || name > 6 ) {
        printf("-1\n");
        return;
    }
    Edge tmp;
    int cnt = 0;
    for (int i = 0; i < VERTEX_NUM; i++) {
        if (M[name - 1][i].destination != NULL) {
            cnt++;
        }
    }
    Edge *print = (Edge *) malloc(sizeof(Edge) * cnt);

    int j = 0;
    for (int i = 0; i < VERTEX_NUM; i++) {
        if (M[name - 1][i].destination != NULL) {
            print[j] = M[name - 1][i];
            j++;
        }
    }

    for (int i = 0; i < cnt; i++) {
        for (j = 0; j < cnt - 1; j++) {
            if (print[j].destination->name > print[j + 1].destination->name) {
                tmp = print[j];
                print[j] = print[j + 1];
                print[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < cnt; i++)
        printf(" %d %d", print[i].destination->name, print[i].weight);
    printf("\n");
}

void modifyGraph(Graph *g, int name1, int name2, int weight, Edge** M) {
    if (name1 < 1 || name1 > 6 || name2 < 1 || name2 > 6) {
        printf("-1\n");
        return;
    }

    Vertex *v1 = &(g->v[name1 - 1]);
    Vertex *v2 = &(g->v[name2 - 1]);

    //삭제
    if (weight == 0) {
        if (M[name1 - 1][name2 - 1].destination == NULL) return;
        else {
            M[name1 - 1][name2 - 1].origin = NULL;
            M[name1 - 1][name2 - 1].destination = NULL;
            M[name1 - 1][name2 - 1].weight = 0;
        }
        //reverse
        if (name1 != name2) {
            M[name2 - 1][name1 - 1].origin = NULL;
            M[name2 - 1][name1 - 1].destination = NULL;
            M[name2 - 1][name1 - 1].weight = 0;
        }

    } else {
        if (M[name1 - 1][name2 - 1].destination == NULL) {
            insertVE(g, name1, name2, weight, M);
            return;
        } else {
            M[name1 - 1][name2 - 1].weight = weight;
        }

        //reverse
        if (name1 != name2) {
            M[name2 - 1][name1 - 1].weight = weight;

        }

    }
}
int main() {
    Graph g;

    Edge **M = (Edge **) malloc(sizeof(Edge *) * VERTEX_NUM);
    for (int i = 0; i < VERTEX_NUM; i++)
        M[i] = (Edge *) malloc(sizeof(Edge) * VERTEX_NUM);

    graphInit(&g, M);
    insertVE(&g, 1, 2, 1, M);
    insertVE(&g, 1, 3, 1, M);
    insertVE(&g, 1, 4, 1, M);
    insertVE(&g, 1, 6, 2, M);
    insertVE(&g, 2, 3, 1, M);
    insertVE(&g, 3, 5, 4, M);
    insertVE(&g, 5, 5, 4, M);
    insertVE(&g, 5, 6, 3, M);

    char order;
    int name;
    int name1, name2, weight;
    while (1) {
        scanf("%c", &order);
        if (order == 'a') {
            scanf("%d", &name);
            printGraph(&g, name, M);
        } else if (order == 'm') {
            scanf("%d %d %d", &name1, &name2, &weight);
            modifyGraph(&g, name1, name2, weight, M);

        } else if (order == 'q') {
            break;
        }
        getchar();
    }
    return 0;
}
 */