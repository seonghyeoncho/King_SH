#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define W 4
#define H 4

int ground[W][H];

int getch(void);

void initGround(void);
void setRandomGround(void);

void slideGame(void);

void printGround(void);
int controlGround(char);

void HomePage(void);

int checkGround(void);

int c1,c2;

int main(){
    

    initGround();
    setRandomGround();

    system("clear");

    slideGame();
    
    return 0;
}

void HomePage(){

    printf("Slide Puzzle Game!!");
    
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
