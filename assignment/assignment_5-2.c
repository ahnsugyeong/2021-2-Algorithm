/*
 * 인접리스트 구조를 사용하였다.
 * DFS를 돌려서 더 이상 갈 곳이 없으면 그 정점에 order를 부여하고(n) n을 감소하고
 * back 하면서 또 더 이상 갈 곳이 없으면 그 정점에 order를 부여하였다.
 * order 부여가 끝나고 다시 main으로 돌아와서
 * 만약 order 부여가 안돼서 아직 그 구조체의 order 변수가 -1이라는 초기값을 가지고 있다면
 * 해당 정점부터 DFS를 다시 돌려서 차마 순회하지 못한 정점에도 위상 순서를 부여해주었다.(예시 2같은 상황)
 * 부여한 order에 따라 그래프의 정점을 오름차순으로 정렬한 후 출력하면 위상 정렬 순서가 출력된다.
 *
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    char name;
    int v_visit;
    struct AdjList* adj;
    int order;
}Vertex;

typedef struct Edge{
    struct Vertex* origin;
    struct Vertex* destination;
    int e_visit;
}Edge;

typedef struct Graph{
    struct Vertex* vertex;
    struct Edge* edge;
}Graph;

typedef struct AdjList{
    struct Edge* edge;
    struct AdjList* next;
}AdjList;

void initGraph(Graph* g, int n, int m){
    g->vertex = (Vertex*)malloc(sizeof(Vertex)*n);
    g->edge = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<n;i++){
        scanf("%c", &g->vertex[i].name);
        getchar();
        g->vertex[i].adj = (AdjList*)malloc(sizeof(AdjList));
        g->vertex[i].adj->next = NULL;
        g->vertex[i].order = -1;
    }
}
int findVertex(Graph* g, int n, char name){
    for(int i=0;i<n;i++){
        if(g->vertex[i].name == name) return i;
    }
    return -1;
}
int n;
void rTopDFS(Graph *g, int N, char name, int *flag){
    if(*flag == 1) return;
    int index = findVertex(g, N, name);
    g->vertex[index].v_visit = 1;

    for(AdjList* p = (g->vertex[index].adj->next);p!=NULL;p=p->next){
        Vertex* w = p->edge->destination;
        if(w->v_visit == 0) rTopDFS(g, N, w->name, flag);
        else if(w->v_visit != 0 && w->order == -1) {
            *flag = 1;
            return;
        }
    }
    if(*flag == 1) return;

    g->vertex[index].order = n;
    n--;
}


void insertVEA(Graph* g, int n, int m){
    char name1, name2;
    Vertex* v1;
    Vertex* v2;

    for(int i=0;i<m;i++){
        scanf("%c %c", &name1, &name2);
        getchar();
        v1 = &(g->vertex[findVertex(g, n, name1)]);
        v2 = &(g->vertex[findVertex(g, n, name2)]);
        Edge* new_edge = (Edge*)malloc(sizeof(Edge));
        new_edge->origin = v1;
        new_edge->destination = v2;


        AdjList* new_adj = (AdjList*)malloc(sizeof(AdjList));
        new_adj->edge = new_edge;

        AdjList* tmp = v1->adj;
        while(tmp->next != NULL){
            if(tmp->next->edge->destination->name < new_edge->destination->name) tmp = tmp->next;
            else break;
        }

        new_adj->next = tmp->next;
        tmp->next = new_adj;


    }
}
int main(){
    int m;
    char s;

    scanf("%d %d %c", &n, &m, &s);
    int N = n;
    getchar();
    Graph g;
    initGraph(&g, n, m);
    insertVEA(&g, n, m);
    int flag= 0;
    rTopDFS(&g, N, s, &flag);
    for(int i=0;i<N;i++){
        if(g.vertex[i].order == -1) {
            rTopDFS(&g, N, g.vertex[i].name, &flag);
        }
    }
    for(int i=0;i<N;i++){

        for(int j=0;j<N-1;j++){
            Vertex tmp;
            if(g.vertex[j].order>g.vertex[j+1].order){
                tmp = g.vertex[j];
                g.vertex[j] = g.vertex[j+1];
                g.vertex[j+1] = tmp;
            }
        }
    }
    if(flag == 1) printf("-1");
    else {
        for (int i = 0; i < N; i++)
            printf(" %c", g.vertex[i].name);
    }
    return 0;
}
