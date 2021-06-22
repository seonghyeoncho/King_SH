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
struct Words {
  char eng[15];
  char kor[30];
  struct Words *next;
};

struct Node* nodeHead = NULL;

struct Words* head = NULL;
struct Words* last = NULL;

#define W 4
#define H 4
int count = 0;
// global val
int ground[W][H];
int c1, c2;
int isLogined;
int moveCount;
double playTime;
char loginedId[100];

//func origin
int getch(void);

//linked list
FILE *openFile_R(int);
FILE *openFile_W(void);
void updateFile(void);

void setNodeUser(FILE*);
void setNodeGame(FILE*);
void freeNode(void);
void freeNode_Game(void);
void freeNode_User(void);

int deleteNode(char*);
int findNode(char*);
void updateNode(char *, int);
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
void menuGame(void);
int game(void);
void quizStart(void);

//game
void menu(void);

void programInit(void);

//page
void signupPage(void);
void signinPage(void);
void signoutPage(void);
void withdrawalPage(void);
void puzzleGamePage(void);
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
                puzzleGamePage();
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
        struct Node* cur = nodeHead;
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
            struct Node* cur = nodeHead;

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
        struct Node* cur = nodeHead;

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
void menuGame(){
  printf(">> 영어 단어 맞추기 프로그램 <<");
  printf("\n1. 영어 단어 맞추기 2. 프로그램 종료\n\n번호를 선택하세요: ");
};
void puzzleGamePage() {
    system("clear");
    sleep(1);
    system("clear");
    if (isLogined != 0) {
        printf("환영합니다! %s\n", loginedId);
        sleep(1);
        system("clear");
        game();
    } else {
        char _ans;
        printf("로그인 상태가 아닙니다.\n게임 결과는 저장되지 않습니다.\n계속하시겠습니까?[y/n]:" );
        scanf("%c", &_ans);
        getch();

        if (_ans == 'y') {
            printf("게임을 시작합니다.\n");
            sleep(1);
            system("clear");
            game();
        } else if (_ans == 'n'){
            printf("메뉴로 돌아갑니다.\n");
            sleep(1);
        } else {
            printf("잘못된 입력입니다. 메뉴로 돌아갑니다.\n");
            sleep(1);
        }
    }
}
int game() {
  int n;

  setNodeGame(openFile_R(2));

  while (1) {
    menuGame();
    scanf("%d",&n);

    switch (n){
      case 1:
        quizStart();
        system("clear");
        break;
      case 2:
        system("clear");
        return 0;
      default:
        break;
    }
  };
};

void quizStart() {
  struct Words* tmp = head;
  char eng_a[30], q[30] = ".quit";
  double cor = 0, incor = 0;

  while (1) {
    printf("%s -> ", tmp->kor);
    scanf("%s", eng_a);
    getchar();

    if (!strcmp(q,eng_a)) break;
    if (!strcmp( tmp->eng, eng_a )) {
        printf("correct!\n");
        cor++;
    } else {
        printf("incorrect!\n");
        incor++;
    }

    if(tmp->next == NULL) break;
    else tmp = tmp->next;
  };
  printf("당신의 점수는 %.2f점입니다.", (cor+incor) == 0 ? 0 : (cor)/(cor+incor)*100);
  getchar();
};
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
            struct Node* cur = nodeHead;
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
    setNodeUser(openFile_R(1));
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

int isNickNameUnique(char* nickName) {
    struct Node* cur = nodeHead;
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
    struct Node* cur = nodeHead;
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
    struct Node* cur = nodeHead;
    int result = findNode(id);
    return result;
}
int isValidPassword(char* password, int index) {
    struct Node* cur = nodeHead;
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
    struct Node* cur = nodeHead;
    while (1) {
        printf("    %d       %.2lf    %s    \n", cur -> rank, cur -> point, cur -> nickName);
        if(cur -> next == NULL) break;
        else cur = cur -> next;
    };
    getch();
}
void setNodeUser(FILE* f) {
    struct Node* cur;

    while(1) {
        struct Node* tempNode = (struct Node*)malloc(sizeof(struct Node));
        
        if (EOF == (fscanf(f,"%s %s %s %s %lf %d %d", tempNode -> nickName, tempNode -> name, tempNode -> id, tempNode -> password, &tempNode -> point, &tempNode -> rank, &tempNode -> state))) {
            break;
        }
        
        if (nodeHead == NULL){
            nodeHead = tempNode;
            tempNode -> next = NULL;
            cur = nodeHead;
        } else {
            cur -> next = tempNode;
            tempNode -> next = NULL;
            cur = cur -> next;
        }
    }

    fclose(f);
}
void setNodeGame(FILE* f) {
  struct Words* cur = NULL;
  struct Words* pre = NULL;
    
  while (1) {
    struct Words* node = (struct Words*)malloc(sizeof(struct Words));
    if(EOF == (fscanf(f,"%s %s",node->eng, node->kor))) break;
    if (head == NULL) {
      head = node;
      node->next = last;
    } else {
      if  (strcmp( node-> eng, head-> eng ) < 0 ) {
        struct Words* tmp = NULL;
        tmp = head;
        head = node;
        head->next = tmp;
      }
      else {
        pre = head;
        cur = pre->next;

        while (1) {
          if (cur == NULL && strcmp( node->eng, pre->eng ) > 0) {
            pre->next = node;
            pre->next->next = cur;
            break;
          } else if (strcmp( node->eng, cur->eng ) < 0) {
              struct Words* tmp = NULL;
              tmp = cur;
              pre->next = node;
              pre->next->next = tmp;
              break;
          } else {
            pre = cur;
            cur = cur->next;
          }
        };
      };
    };
    count++;
  };
  fclose(f);
};
void freeNode() {
    freeNode_User();
    freeNode_Game();
}
void freeNode_User() {
    struct Node* node = nodeHead;
    struct Node* tmp = nodeHead;

    while(tmp){
        node = tmp -> next;
        free(tmp);
        tmp = node;
    };
}
void freeNode_Game() {
    struct Words* node = head;
    struct Words* tmp = head;

    while(tmp){
        node = tmp->next;
        free(tmp);
        tmp = node;
    };
}
int deleteNode(char* id) {
    struct Node* cur = nodeHead;
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
    struct Node* cur = nodeHead;
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
void updateNode(char *id, int action) {
    struct Node* cur = nodeHead;
    
    while (cur != NULL) {
        if (strcmp(id, cur -> id)) {
            if (action == 1) {
                //name

            } else if (action == 2) {
                //nickname
            } else if (action == 3) {
                cur -> point = playTime + moveCount;
                playTime = 0;
                moveCount = 0;
            }
            break;
        }
        cur = cur -> next;
    }

    if (cur == NULL) {
        printf("유효하지 않은 id입니다.\n");
    }
}
void updateFile() {
    struct Node* cur = nodeHead;
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
    struct Node* cur = nodeHead;

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
        return f;
    }   

    return 0;
}
FILE* openFile_R(int fileNumber) {
    FILE *f;
    switch (fileNumber) {
        case 1:
            if((f = fopen("client.txt", "r")) == NULL){
                printf("Error : Can not open file.\n");
                exit(0);
            } else return f; 
            break;
        case 2:
            if((f = fopen("dict.txt", "r")) == NULL){
                printf("파일을 열 수가 없습니다.\n");
                exit(0);
            } else return f;
        default:
            break;
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