#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct Node {

    char name[100];
    char nickName[100];
    char id[100];
    char password[100];
    double point;
    int rank;
    int state;

    struct Node* next;
};

//file
FILE *openFile_R(void);
FILE *openFile_W(void);

//node
void setNode(FILE*);
void freeNode(void);

//api
int deleteNode(char*);
int findNode(char*);
void updateNode(void);
void insertNode(struct Node*);

void showPlayer(void);

struct Node* head = NULL;



int main() {
    //test code
    setNode(openFile_R());
    showPlayer();
    deleteNode("chosh000");
    struct Node* tempNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(tempNode -> nickName, "nick");
    strcpy(tempNode -> name, "조성현2");
    strcpy(tempNode -> id, "qwerty");
    strcpy(tempNode -> password, "12345");
    tempNode -> point = 0;
    tempNode -> rank = 0;
    tempNode -> state = 0;
    tempNode -> next = NULL;
    insertNode(tempNode);

    showPlayer();
    updateNode();
    showPlayer();



    freeNode();

    return 0;
}

void showPlayer() {
    struct Node* cur = head;

    while (1) {
        printf("nick name: %s\n", cur -> nickName);
        printf("point: %lf\n", cur -> point);
        printf("rank: %d\n", cur -> rank);
        if(cur -> next == NULL) break;
        else cur = cur -> next;
    };
}

void setNode(FILE* f) {
    struct Node* cur;

    while(1) {
        struct Node* tempNode = (struct Node*)malloc(sizeof(struct Node));
        
        if (EOF == (fscanf(f,"%s %s %s %s %lf %d %d", tempNode -> nickName, tempNode -> name, tempNode -> id, tempNode -> password, &tempNode -> point, &tempNode -> rank, &tempNode -> state))) {
            break;
        }
        
        if (head == NULL){
            head = tempNode;
            tempNode -> next = NULL;
            cur = head;
        } else {
            cur -> next = tempNode;
            tempNode -> next = NULL;
            cur = cur -> next;
        }
    }

    fclose(f);
};

void freeNode() {
    struct Node* node = head;
    struct Node* tmp = head;

    while(tmp){
        node = tmp -> next;
        free(tmp);
        tmp = node;
    };
};

int deleteNode(char* id) {
    struct Node* cur = head;
    int result = findNode(id);

    if(result == -99999) {
        printf("no data for delete.\n");
    } else {
        struct Node* tempNode = (struct Node*)malloc(sizeof(struct Node));
        struct Node* prevNode = (struct Node*)malloc(sizeof(struct Node));
        int tempIndex = result;

        while (tempIndex--) {
            if (tempIndex == 0) {
                prevNode = cur;
            }
            cur = cur -> next;
        }
        tempNode = cur -> next;
        prevNode -> next = tempNode;
        free(cur);
    }

    return result;
}

int findNode(char* id) {
    struct Node* cur = head;
    int result = -99999;
    int index = 0;

    while (cur != NULL) {
        if (strcmp(id, cur -> id) == 0) {
            result = index;
            return result;
        } else {
            cur = cur -> next;
        }
        index++;
    }

    return result;
}

void updateNode() {
    struct Node* cur = head;
    FILE* f = openFile_W();

    while (cur != NULL) {
        if (cur -> next == NULL) {
            fprintf(f, "%s %s %s %s %lf %d %d", cur -> nickName, cur -> name, cur -> id, cur -> password, cur -> point, cur -> rank, cur -> state);
        } else {
            fprintf(f, "%s %s %s %s %lf %d %d\n", cur -> nickName,cur -> name, cur -> id, cur -> password, cur -> point, cur -> rank, cur -> state);
        }
        cur = cur -> next;
    }
    fclose(f);
}

void insertNode(struct Node* data) {
    struct Node* cur = head;

    while (cur -> next != NULL) {
        cur = cur -> next;
    }
    cur -> next = data;
}

FILE* openFile_W() {
    FILE *f;

    if((f = fopen("client.txt", "w")) == NULL){
        printf("Error : Can not open file.\n");
        exit(0);
    } else {
        printf("Success.\n");
        return f;
    }   

    return 0;
};
FILE* openFile_R() {
    FILE *f;

    if((f = fopen("client.txt", "r")) == NULL){
        printf("Error : Can not open file.\n");
        exit(0);
    } else {
        printf("Success.\n");
        return f;
    }   

    return 0;
};