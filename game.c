#include <stdio.h>
#include <unistd.h>
#include <conio.h>


#define WIDTH 10
#define HEIGHT 20
#define UPDATEDELAY 1500000

int board[HEIGHT][WIDTH];
int updateDelayCounter = 0;
int score = 0;
char gameOpen = 1;
// int current_x = WIDTH/2;
// int current_y = 0;

// typedef struct{
//     char shape;
//     int x;
//     int y;
// } piece;

// piece myPiece = {.shape = 'l' .x = WIDTH/2 .y=0};

void initializeBoard();
void printBoard();
void updateBoard();
void clearRow(int row);
char fallCheck();
void initializePiece();

int main(int argc, char * argv[]){

    initializeBoard();
    printBoard();
    while(gameOpen){
        

        if (_kbhit()) {             // check if a key is pressed
            char c = _getch();      // get char without waiting for Enter
            if (c == 'q'){
                gameOpen = 0;
                
            }
        }

        updateBoard();
    }

    printf("Game Exited\n");
    
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
    board[11][5] = 0;
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
}

char fallCheck(){
    for(int j = 0; j<WIDTH; j++){
        if(board[HEIGHT-1][j] == 1){
            return 0;
        }
    }
    return 1;
}

void initializePiece(){
    int current_x = WIDTH/2;
    int current_y = 0;
}