#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void setNode(FILE *);  
void freeNode(void);
void quizStart(void);
FILE* openFile(void);
void menu(void);

int count = 0;

struct Words {
  char eng[15];
  char kor[30];
  struct Words *next;
};

struct Words* head = NULL;
struct Words* last = NULL;

int main(){
  int n;
  setNode(openFile());
  while(1){
    menu();
    scanf("%d",&n);
    switch (n){
      case 1:
          quizStart();
          system("clear");
          break;
      case 2:
          freeNode();
          system("clear");
          return 0;
      default:
          break;
    }
  };
  return 0;
};

void menu(){
  printf(">> 영어 단어 맞추기 프로그램 <<");
  printf("\n1. 영어 단어 맞추기 2. 프로그램 종료\n\n번호를 선택하세요: ");
};

FILE* openFile(){
  FILE *f;
  if((f = fopen("dict.txt", "r")) == NULL){
      printf("파일을 열 수가 없습니다.\n");
      exit(0);
  } else return f;
  return 0;
};

void setNode(FILE* f) {
  struct Words* cur = NULL;
  struct Words* pre = NULL;
    
  while (1) {
    struct Words* node = (struct Words*)malloc(sizeof(struct Words));
    if(EOF == (fscanf(f,"%s %s",node->eng, node->kor))) break;
    if (head == NULL) {
      head = node;
      node->next = last;
    } else {
      if  (strcmp( node->eng, head->eng ) < 0 ) {
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
  struct Words* node = head;
  struct Words* tmp = head;

  while(tmp){
    node = tmp->next;
    free(tmp);
    tmp = node;
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
