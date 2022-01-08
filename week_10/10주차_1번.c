#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex{
    int name;
    struct AdjList* adj;
}Vertex;

typedef struct Edge{
    int weight;
    struct Vertex* origin;
    struct Vertex* destination;
}Edge;

typedef struct AdjList{
    struct Edge* edge;
    struct AdjList* next;
}AdjList;

typedef struct Graph{
    Vertex vertex[6];
    Edge edge[8];
}Graph;

void initGraph(Graph* g){
    for(int i=0;i<6;i++){
        g->vertex[i].name = i+1;
        g->vertex[i].adj = (AdjList*)malloc(sizeof(AdjList));
        g->vertex[i].adj->next = NULL;
    }
}

void insertAdjList(Vertex* v, Edge* e){
    AdjList* new_adj = (AdjList*)malloc(sizeof(AdjList));
    new_adj->edge = e;

    Vertex* op;
    if(e->origin == v) op = e->destination;
    else op = e->origin;

    AdjList* tmp = v->adj;

    while(tmp->next != NULL){
        if(tmp->next->edge->origin == v){
            if(tmp->next->edge->destination->name < op->name){
                tmp = tmp->next;
            }
            else break;
        }
        else{
            if(tmp->next->edge->origin->name < op->name){
                tmp = tmp->next;
            }
            else break;
        }
    }
    new_adj->next = tmp->next;
    tmp->next = new_adj;
}

void insertVE(Graph* g, int name1, int name2, int w){
    if(name1<1||name1>6||name2<1||name2>6){
        printf("-1\n");
        return;
    }
    Vertex* v1 = &(g->vertex[name1-1]);
    Vertex* v2 = &(g->vertex[name2-1]);

    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->weight = w;
    new_edge->origin = v1;
    new_edge->destination = v2;

    insertAdjList(v1, new_edge);
    if(v1!=v2) insertAdjList(v2, new_edge);
}

void modifyGraph(Graph* g, int name1, int name2, int w){
    if(name1<1||name1>6||name2<1||name2>6){
        printf("-1\n");
        return;
    }
    Vertex* v1 = &(g->vertex[name1-1]);
    Vertex* v2 = &(g->vertex[name2-1]);


    //v1
    int flag = 0;
    AdjList* tmp1 = v1->adj;
    while(tmp1->next!=NULL){
        if(tmp1->next->edge->origin == v1){
            if(tmp1->next->edge->destination == v2){
                flag = 1;
                break;
            }
        }
        else{
            if(tmp1->next->edge->origin == v2){
                flag = 1;
                break;
            }
        }
        tmp1 = tmp1->next;
    }

    //v2
    AdjList* tmp2 = v2->adj;
    while(tmp2->next!=NULL){
        if(tmp2->next->edge->origin == v2){
            if(tmp2->next->edge->destination == v1){
                flag = 1;
                break;
            }
        }
        else{
            if(tmp2->next->edge->origin == v1){
                flag = 1;
                break;
            }
        }
        tmp2 = tmp2->next;
    }
////////////////////////////

    if(w == 0){
        // 존재하지 않고 w가 0이면 return
        if(flag == 0) return;
        else{
            // 존재하는데 w가 0이면 삭제
            AdjList* free_tmp = tmp1->next;
            tmp1->next = tmp1->next->next;
            free(free_tmp);
            //reverse
            if(name1 != name2) {
                free_tmp = tmp2->next;
                tmp2->next = tmp2->next->next;
                free(free_tmp);
            }
        }
    }
    else{
        // 존재하지 않고 w가 0이 아니면 추가
        if(flag == 0) insertVE(g, name1, name2, w);
        else {
            // 존재하고 w가 0이 아면 수정
            tmp1->next->edge->weight = w;
            if(name1 != name2) tmp2->next->edge->weight = w;
        }
    }


}

void searchAdjVertex(Graph* g, int name){
    if(name<1||name>6){
        printf("-1\n");
        return;
    }
    Vertex* v = &(g->vertex[name-1]);

    // v->adj는 header node 역할이다!
    AdjList* tmp = v->adj->next;
    while(tmp != NULL){
        if(tmp->edge->origin == v){
            printf(" %d %d", tmp->edge->destination->name, tmp->edge->weight);
        }
        else printf(" %d %d", tmp->edge->origin->name, tmp->edge->weight);

        tmp = tmp->next;
    }
    printf("\n");
}


int main(){
    Graph g;
    initGraph(&g);
    insertVE(&g, 1, 2, 1);
    insertVE(&g, 1, 3, 1);
    insertVE(&g, 1, 4, 1);
    insertVE(&g, 1, 6, 2);
    insertVE(&g, 2, 3, 1);
    insertVE(&g, 3, 5, 4);
    insertVE(&g, 5, 5, 4);
    insertVE(&g, 5, 6, 3);

    char order;
    int name;
    int name1, name2, w;
    while(1){
        scanf("%c", &order);
        if(order == 'a'){
            scanf("%d", &name);
            searchAdjVertex(&g, name);
        }
        else if(order == 'm'){
            scanf("%d %d %d", &name1, &name2, &w);
            modifyGraph(&g, name1, name2, w);
        }
        else if(order == 'q'){
            break;
        }
        getchar();
    }


    return 0;
}