#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
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

#define W 4
#define H 4

// global val
int ground[W][H];
int c1, c2;
int isLogined;
struct Node* head = NULL;

//func origin
int getch(void);

//linked list
FILE *openFile_R(void);
FILE *openFile_W(void);

void setNode(FILE*);
void freeNode(void);

int deleteNode(char*);
int findNode(char*);
void updateNode(void);
void insertNode(struct Node*);

void showPlayer(void);

void loginPage(void);
int getLoginState(char*, char*);
int isValidId(char*);
int isValidPassword(char*, int);

void signupPage();
int isIdUnique(char*);
int isNickNameUnique(char*);

//sliding puzzle
void initGround(void);
void setRandomGround(void);

void slideGame(void);

void printGround(void);
int controlGround(char);

void HomePage(void);

int checkGround(void);

//game
void menu(void);

void programInit(void);

//page
void signupPage(void);
void signinPage(void);
void signoutPage(void);
void withdrawalPage(void);
void slidingGamePage(void);
void searchPlayerPage(void);
void exitPage(void);

int main() {
    programInit();

    while (1) {
        menu();

        int page;
        printf(":");
        scanf("%d", &page);
        
        switch (page) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                exitPage();
                return 0;
            default:
                printf("not found page.\n");
        }
        system("clear");
    }

    return 0;
}
void signinPage() {

}
void signoutPage() {

}
void withdrawalPage() {

}
void slidingGamePage() {

}
void searchPlayerPage() {

}
void programInit() {
    isLogined = 0;
    system("clear");
    // setNode(openFile_R());
}
void exitPage() {
    printf("see you next time!!\n");
    // freeNode();
}
void menu() {
    printf("========== SLIDING GAME ==========\n");
    printf("==================================\n");
    printf("=              menu              =\n");
    printf("=           1. sign up           =\n");
    printf("=           2. sign in           =\n");
    printf("=           3. start             =\n");
    printf("=           4. players           =\n");
    printf("=           5. sign out          =\n");
    printf("=        6. delete player        =\n");
    printf("=           7. exit              =\n");
    printf("==================================\n");
}

int getch(void){
    int ch;
    struct termios buf;
    struct termios save;

    tcgetattr(0,&save);

    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;

    tcsetattr(0,TCSAFLUSH,&buf);
    ch = getchar();
    tcsetattr(0,TCSAFLUSH,&save);
    
    return ch;
}
int isNickNameUnique(char* nickName) {
    struct Node* cur = head;
    int result = 0;

    while (cur != NULL) {
        if (strcmp(nickName, cur -> nickName) == 0) {
            result = 1;
            break;
        }
        cur = cur -> next;
    }

    return result;
}
int isIdUnique(char* id) {
    struct Node* cur = head;
    int result = 0;

    while (cur != NULL) {
        if (strcmp(id, cur -> id) == 0) {
            result = 1;
            break;
        }
        cur = cur -> next;
    }

    return result;
}
void signupPage() {
    
    char _id[100];
    char _password[100];
    char _name[100];
    char _nickName[100];
    
    while (1) {
        printf("id: ");
        scanf("%s", _id);

        if (isIdUnique(_id) != 0) {
            printf("already exist id.\n");
            continue;
        } else {
            printf("good id!\n");
        }

        printf("password: ");
        scanf("%s", _password);
        break;
    }

    while (1) {
        printf("nickname: ");
        scanf("%s", _nickName);
         if (isNickNameUnique(_nickName) != 0) {
            printf("already exist nickname\n");
            continue;
        } else {
            printf("good nickname!\n");
        }
        printf("name: ");
        scanf("%s", _name);
        break;
    }
    
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node -> id, _id);
    strcpy(node -> password, _password);
    strcpy(node -> nickName, _nickName);
    strcpy( node -> name, _name);
    node -> point = 0;
    node -> rank = 0;
    node -> state = 0;
    node -> next = NULL;

    insertNode(node);

    printf("complete sign up! hello!\n");
}

void loginPage() {
    int loginState;
    struct Node* cur = head;
    char tempId[100];
    char tempPassword[100];

    while (1) {
        
        printf("id : ");
        scanf("%s", tempId);
        printf("password : ");
        scanf("%s", tempPassword);

        loginState = getLoginState(tempId, tempPassword);
        if (loginState == -99999) {
            printf("error id or password. please again.\n");
            continue;
        } else {
            printf("success!\n");
            break;
        }
    }

    while (loginState--) {
        cur = cur -> next;
    }
    cur -> state = 1;
    printf("welcom! %s\n", cur -> nickName);

}
int isValidId(char* id) {
    struct Node* cur = head;
    int result = findNode(id);
    return result;
}
int isValidPassword(char* password, int index) {
    struct Node* cur = head;
    int tempIndex = index;
    int result = 0;
    while (tempIndex--) {
        cur = cur -> next;
    }
    if (!strcmp(password, cur -> password)) {
        result = 1;
    } 
    return result;
}
int getLoginState(char* tempId, char* tempPassword) {
    int result = -99999;

    int checkId = isValidId(tempId);
    if (checkId == -99999) {
        return result;
    } else {
        result = checkId;
    }
    int checkPassword = isValidPassword(tempPassword, checkId);
    if (!checkPassword) {
        result = -99999;
    } 

    return result;
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
}
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
}