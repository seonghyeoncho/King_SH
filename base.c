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


int main() {
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