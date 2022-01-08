#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student{
    char ID[9];
    char name[21];
}Student;

Student* findID(Student* s, char* k, int l, int r){
    while (l <= r) {
        int mid = (l + r) / 2;
        if(strcmp(k, s[mid].ID) == 0){
            return &s[mid];
        }
        else if (strcmp(k, s[mid].ID) < 0) {
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return NULL;
}
int main(){
    int N;
    scanf("%d", &N);
    Student* s = (Student *)malloc(sizeof(Student)*N);


    for(int i=0;i<N;i++){
        scanf("%s %s", s[i].ID, s[i].name);
    }

    char who[9];
    scanf("%s", who);


    Student* res = NULL;
    res = findID(s, who, 0, N-1);


    if(res == NULL) printf("-1\n");
    else printf("%s %s\n", res->ID, res->name);

    free(s);

    return 0;
}
