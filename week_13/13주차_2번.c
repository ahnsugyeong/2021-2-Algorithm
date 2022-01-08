#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int vertex1, vertex2;
    int weight;
}Edge;

typedef struct Incident {
    int edge;
    struct Incident* next;
}Incident;

typedef struct Vertex {
    int name;
}Vertex;

typedef struct Seperate {
    int size;
    Incident* head;
}Seperate;

typedef struct Graph {
    Vertex* vertex;
    Edge* edge;
    int n, m;
}Graph;

typedef struct Heap {
    int key;
    int weight;
}Heap;

int findIndex(Graph* g, int name){
    for(int i=1;i<=g->n;i++){
        if(g->vertex[i].name == name) return i;
    }
}

void initGraph(Graph* g, int n, int m) {
    g->n = n;
    g->m = m;
    g->vertex = (Vertex*)malloc(sizeof(Vertex) * (n + 1));
    g->edge = (Edge*)malloc(sizeof(Edge) * m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &g->vertex[i].name);
    }
}

void insertIncidentEdge(Graph* g, int v1, int v2, int w, int idx) {
    g->edge[idx].vertex1 = v1;
    g->edge[idx].vertex2 = v2;
    g->edge[idx].weight = w;
}

void buildGraph(Graph* g) {
    int n, m;
    int v1, v2, w;

    scanf("%d %d", &n, &m);

    initGraph(g, n, m);

    for (int i = 0; i < g->m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);
        insertIncidentEdge(g, v1, v2, w, i);
    }
}



Seperate* buildSet(Graph* g) {
    Seperate* set = (Seperate*)malloc(sizeof(Seperate) * g->n);

    for (int i = 0; i < g->n; i++) {
        set[i].size = 0;
        set[i].head = (Incident*)malloc(sizeof(Incident));
        set[i].head->edge = g->vertex[i + 1].name;
        set[i].head->next = NULL;
    }

    return set;
}
void swapElem(Heap* x, Heap* y) {
    Heap temp;

    temp = *x;
    *x = *y;
    *y = temp;
}
void downHeap(Heap* heap, int idx, int size) {
    int left = 2 * idx;
    int right = 2 * idx + 1;
    int smaller;

    if (left > size) return;

    smaller = left;
    if (right <= size) {
        if (heap[right].weight < heap[left].weight) {
            smaller = right;
        }
    }

    if (heap[idx].weight <= heap[smaller].weight) return;

    swapElem(heap + idx, heap + smaller);
    downHeap(heap, smaller, size);
}



int removeMin(Heap* heap, int idx) {
    Heap remove;

    if (idx == 0) return -1;

    remove = heap[1];
    swapElem(heap + 1, heap + idx);
    downHeap(heap, 1, --idx);

    return remove.key;
}

void addFirst(Incident** head, int idx) {
    Incident* node = (Incident*)malloc(sizeof(Incident));
    node->edge = idx;
    node->next = *head;
    *head = node;
}

int deleteFirst(Incident** head) {
    int remove;

    if (*head == NULL) return -1;

    remove = (*head)->edge;
    *head = (*head)->next;

    return remove;
}
Heap* buildHeap(Graph* g) {
    Heap* heap = (Heap*)malloc(sizeof(Heap) * (g->m + 1));
    int i;

    for (i = 1; i <= g->m; i++) {
        heap[i].weight = g->edge[i - 1].weight;
        heap[i].key = i;
    }

    for (i = g->m / 2; i >= 1; i--) {
        downHeap(heap, i, g->m);
    }

    return heap;
}

int findSet(Graph* g, Seperate* set, int v) {
    Incident* p;

    for (int i = 0; i < g->n; i++) {
        p = set[i].head;
        while (p != NULL) {
            if (g->vertex[p->edge].name == v) return i;
            p = p->next;
        }
    }
    return -1;
}

void unionSet(Seperate* set, int v1, int v2) {
    int temp, i;

    if (set[v1].size < set[v2].size) {
        temp = v1;
        v1 = v2;
        v2 = temp;
    }

    while (1) {
        i = deleteFirst(&(set[v2].head));

        if (i == -1) break;

        addFirst(&(set[v1].head), i);
    }

    set[v2].head = NULL;
    set[v2].size = 0;
}

void freeSet(Graph* g, Seperate* set) {
    Incident* p, * next;

    for (int i = 0; i < g->n; i++) {
        p = set[i].head;

        while (p != NULL) {
            next = p->next;
            free(p);
            p = next;
        }
    }
    free(set);
}

void kruskalMST(Graph* g) {
    Seperate* set = buildSet(g);
    Heap* heap = buildHeap(g);
    int size = g->m;
    int sum = 0;
    int u, v1, v2;

    while (size > 0) {

        u = removeMin(heap, size);
        printf("\nu = %d\n", u);
        v1 = findSet(g,set, g->edge[u - 1].vertex1);
        v2 = findSet(g,set, g->edge[u - 1].vertex2);

        if (v1 != v2) {
            printf("%d %d %d\n",g->edge[u-1].vertex1, g->edge[u-1].vertex2, g->edge[u - 1].weight);
            sum += g->edge[u - 1].weight;
            unionSet(set, v1, v2);
        }
        size--;
    }

    printf("%d", sum);
    freeSet(g, set);
    free(heap);
}



void freeGraph(Graph* g) {
    free(g->vertex);
    free(g->edge);
}




int main() {
    Incident* head;
    Graph g;
    buildGraph(&g);

    kruskalMST(&g);
    freeGraph(&g);

    return 0;
}
/*
6 9
0 1 2 3 4 5
0 1 3
0 2 20
1 3 25
1 4 17
2 3 34
2 4 1
2 5 12
3 4 5
4 5 37
 1 2 5 3 6 7 4
 */