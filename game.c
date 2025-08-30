#include <stdio.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20
#define UPDATEDELAY 1500000

int board[HEIGHT][WIDTH];
int updateDelayCounter = 0;
int score = 0;


void initializeBoard();
void printBoard();
void updateBoard();
void clearRow(int row);
char fallCheck();

int main(int argc, char * argv[]){

    initializeBoard();
    printBoard();
    while(1){
        updateBoard();
    }
    
}


void initializeBoard(){
    for(int i=0; i<HEIGHT; i++){
        for(int j = 0; j<WIDTH; j++){
            if(i>10){
                board[i][j] = 1;
            }else{
                board[i][j] = 0;
            }
        }
    }

    board[8][8] = 1;
    board[7][7] = 1;
    board[6][6] = 1;
}

void printBoard(){

    printf("\033[H\033[J");

    for(int i = 0; i<HEIGHT; i++){
        for(int j = 0; j< WIDTH; j++){

            if(board[i][j] == 1){
                printf("|%c%c", 219, 219);
            }else{
                printf("|  ");
            }
        }
        printf("|\n");
    }
    printf("\n");
    printf("Score: %d\n", score);
}

void updateBoard(){

    int clearedLines = 0;

    for(int i = HEIGHT-1; i>0; i--){
        char found = 1;
        // printf("checking row %d\n", i);
        for(int j = 0; j<WIDTH; j++ ){
            if(board[i][j] == 0){
                found = 0;
                
            }
        }

        if(found){
            clearedLines ++;
            clearRow(i);
            i = HEIGHT;
        }
    }

    score += clearedLines * 100;

    
    

    if(fallCheck()){
        for(int i = HEIGHT-1; i> 0; i--){
            for(int j = 0; j<WIDTH; j++){
                board[i][j] = board[i-1][j];
            }
        }
        
        for(int j = 0; j<WIDTH; j++){
            board[0][j] = 0;
        }
    }
    

    printBoard();
    usleep(UPDATEDELAY);
    


}

void clearRow(int row){
    for(int i = row; i> 0; i--){
        for(int j = 0; j<WIDTH; j++){
            board[i][j] = board[i-1][j];
        }
    }

    for(int j = 0; j<WIDTH; j++){
        board[0][j] = 0;
    }

    // printf("cleared row: %d\n", row);
}

char fallCheck(){
    for(int j = 0; j<WIDTH; j++){
        if(board[HEIGHT-1][j] == 1){
            return 0;
        }
    }
    return 1;
}