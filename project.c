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
char loginedId[100];
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
void sortNodes(void);

void showAllPlayer(void);

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
void playerPage(void);
void playerPageForSerach();
void playerPageForShowAll();
void exitPage(void);

int main() {
    programInit();

    while (1) {
        menu();

        int page;
        printf(":");
        scanf("%d", &page);
        getch();
        
        switch (page) {
            case 1:
                signupPage();
                break;
            case 2:
                signinPage();
                break;
            case 3:
                slidingGamePage();
                break;
            case 4:
                playerPage();
                break;
            case 5:
                signoutPage();
                break;
            case 6:
                withdrawalPage();
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
void signupPage() {
    system("clear");
    printf("Sign up Page\n");

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

    getch();
}
void signinPage() {
    if (isLogined == 0) {
        system("clear");
        printf("Sign in Page\n");

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

        isLogined = 1;
        strcpy(loginedId, cur -> id);
        printf("welcom! %s\n", cur -> nickName);

    } else {
        printf("already logined! back to menu\n");
    }
    getch();
}
void signoutPage() {
    char ans;
    if (isLogined == 1) {
        printf("Do you want to sign out? [y/n]: ");
        scanf("%c", &ans);
        getch();

        if (ans == 'y') {
            isLogined = 0;
            struct Node* cur = head;

            while (1) {
                if (strcmp(loginedId, cur -> id)) {
                    cur -> state = 0;
                    break;
                } else {
                    cur = cur -> next;
                }
            }
            printf("bye %s\n", cur -> name);
        } else if (ans == 'n') {
            printf("back to menu.\n");
        } else {
            printf("wrong answer.\n ");
        }
    } else {
        printf("Not logined. Please login first.\n");
    }

    getch();
}
void withdrawalPage() {
    if (isLogined != 0) {
        struct Node* cur = head;

        while (1) {
            if (strcmp(loginedId, cur -> id)) {
                break;
            } else {
                cur = cur -> next;
            }
        }

        char c;
        printf("정말 회원을 탈퇴하시겠습니까? [y/n]: ");
        scanf("%c", &c);

        if (c == 'y') {
            if (isLogined == 1) {
                isLogined = 0;
                strcpy(loginedId, " ");
            }
            deleteNode(loginedId);
            printf("회원 탈퇴가 완료되었습니다.");
        } else if (c == 'n') {
            printf("회원 탈퇴를 취소합니다. 메뉴화면으로 돌아갑니다.");
        } else {
            printf("잘못된 입력입니다. 메뉴화면으로 돌아갑니다.");
        }
    } else {
        printf("로그인 상태가 아닙니다.\n");
    }
     getch();
}
void slidingGamePage() {
    initGround();
    setRandomGround();

    system("clear");
    printf("Slide Puzzle Game\n");
    sleep(3);
    system("clear");
    if (isLogined != 0) {
        printf("환영합니다! %s\n", loginedId);
        sleep(3);
    } else {
        char _ans;
        printf("로그인 상태가 아닙니다. 게임 결과는 저장되지 않습니다. 계속하시겠습니까?[y/n]:" );
        scanf("%c", &_ans);

        if (_ans == 'y') {
            printf("게임을 시작합니다.\n");
        } else if (_ans == 'n'){
            printf("게임으로 돌아갑니다.\n");
        } else {
            printf("잘못된 입력입니다. 게임으로 돌아갑니다.\n");

        }
    }
    slideGame();
}
void playerPage() {
    system("clear");

    int select;
    printf("============= PLAYER =============\n");
    printf("==================================\n");
    printf("= 1. search player 2. all player =\n");
    printf("==================================\n");

    scanf("%d", &select);

    while (1) {
        if (select == 1) {
            playerPageForSerach();
            break;
        } else if (select == 2) {
            playerPageForShowAll();
            break;
        } else {
            printf("잘못된 입력입니다. 다시입력해주세요\n");
            break;
        }
    }
}
void playerPageForSerach() {
    char inputForserach[100];
    system("clear");
    while (1) {
        system("clear");
        printf("search(exit: 0):");
        scanf("%s", inputForserach);

        if (strcmp(inputForserach, "0") == 0) {
            printf("exit\n");
            break;
        } else {
            struct Node* cur = head;
            int isExist = 0;
            while (cur != NULL) {
                if (strstr(cur -> nickName, inputForserach) != NULL) {
                    isExist = 1;
                }
                cur  = cur -> next;
            }
            if (isExist != 0) {
                printf("|  Rank  |  NickName  |  Point  |\n");
                    while (cur != NULL) {
                    if (strstr(cur -> nickName, inputForserach) != NULL) {
                        printf("    %d       %.2lf    %s    \n", cur -> rank, cur -> point, cur -> nickName);
                    }
                    cur  = cur -> next;
                }
            } else {
                printf("찾으시는 플레이어가 없습니다.\n");
            }
        }
        getch();
        getch();
    }
    getch();
}
void playerPageForShowAll() {
    system("clear");
    printf("|  Rank  |  NickName  |  Point  |\n");
    showAllPlayer();
    getch();
}
void programInit() {
    isLogined = 0;
    system("clear");
    setNode(openFile_R());
}
void exitPage() {
    system("clear");
    printf("see you next time!!\n");
    freeNode();
}
void showAllPlayerPage() {
    showAllPlayer();
}
void menu() {
    printf("==================================\n");
    printf("========== SLIDING GAME ==========\n");
    isLogined == 0 ? printf("======================== not login\n") : printf("======================== %s\n", loginedId);
    printf("==================================\n");
    printf("=              menu              =\n");
    printf("==================================\n");
    printf("=           1. sign up           =\n");
    printf("=           2. sign in           =\n");
    printf("=           3. start             =\n");
    printf("=           4. players           =\n");
    printf("=           5. sign out          =\n");
    printf("=        6. delete player        =\n");
    printf("=           7. exit              =\n");
    printf("==================================\n");
}
void initGround(){
    int n = 1;
    for(int i = 0 ;i<H;i++){
        for(int k = 0;k<W;k++){
            
            ground[i][k] = n;
            n++;
        }
    }
    ground[W-1][H-1] = 0;
}
void setRandomGround(){
    
    srand(time(NULL));

    int n = 256;
    char c;
    
    while(n--){
        int i = rand()%4;
        switch(i){
            case 0:
                c = 'j';
                break;
            case 1:
                c = 'i';
                break;
            case 2:
                c = 'k';
                break;
            case 3:
                c = 'l';
                break;
            default:
                break;
        }
        controlGround(c);
    }
}
void printGround(){
    printf("          ");

    for(int i = 0 ;i<H;i++){
        for(int k = 0;k<W;k++){
            if(ground[i][k] != 0) printf("%-4d",ground[i][k]);
            else printf("    ");
        }
        printf("\n          ");
    }
    
}
int checkGround(){
    int prev = ground[0][0],cur;
    
    if(prev != 1) return 0;
    
    for(int i = 0;i<H;i++){
        for(int k = 0;k<W;k++){
            cur = ground[i][k];

            if(cur == 1) continue;
            if(prev - cur == 15) return 1;
            if(cur - prev != 1) return 0;
            else prev = cur;
        }
    }
    
    return 0;
}
int controlGround(char c){
    int i,k;   
        
    for(int j = 0 ;j<H;j++){
        for(int h = 0;h<W;h++){
            if(ground[j][h] == 0){
                i = j;
                k = h;
            }
        }
    }
        
    if(c == '0') return 0;
        
    switch (c) {
        case 'j'://L
            if(k != 3 && ground[i][k+1] != 0){   
                ground[i][k] = ground[i][k + 1];
                ground[i][k+1] = 0;    
            }
            break;
        case 'i'://U
            if(i != 3 && ground[i+1][k] != 0){    
                ground[i][k] = ground[i+1][k];
                ground[i+1][k] = 0;    
            }
            break;
        case 'k'://D
            if(i != 0 && ground[i-1][k] != 0){     
                ground[i][k] = ground[i-1][k];
                ground[i-1][k] = 0;  
            }
            break;
        case 'l'://R
            if(k != 0 && ground[i][k-1] != 0){  
                ground[i][k] = ground[i][k - 1];
                ground[i][k-1] = 0;  
            }
            break;
        default:
            break;
    }
        
    return 1; 
}
void slideGame(){
    while(1){
        printGround();

        char c = getch();

        if(!controlGround(c)) break;

        system("clear");

        if(checkGround()) {
            printGround();
            printf("축하합니다!\n");
            sleep(3);
            break;
        }
    }
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
void showAllPlayer() {
    struct Node* cur = head;
    while (1) {
        printf("    %d       %.2lf    %s    \n", cur -> rank, cur -> point, cur -> nickName);
        if(cur -> next == NULL) break;
        else cur = cur -> next;
    };
    getch();
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
}
void freeNode() {
    struct Node* node = head;
    struct Node* tmp = head;

    while(tmp){
        node = tmp -> next;
        free(tmp);
        tmp = node;
    };
}
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
void sortNodes() {

}
FILE* openFile_W() {
    FILE *f;

    if((f = fopen("client.txt", "w")) == NULL){
        printf("Error : Can not open file.\n");
        exit(0);
    } else {
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
        return f;
    }   

    return 0;
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