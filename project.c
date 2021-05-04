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