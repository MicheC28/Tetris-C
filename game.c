#include <stdio.h>
#include <unistd.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 20
#define UPDATEDELAY 1500000

typedef struct {
    int rotations;
    int view[4][5][5]; // up to 4 rotations, each 5x5
} Shape;

Shape shapes[7] = {
    // Vertical Block (I)
    {2, {
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0}
        }
    }},
    
    // T Block
    {4, {
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,1,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,1,1,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,1,1,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,1,1,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        }
    }},

    // L Block
    {4, {
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,1,0},
            {0,1,1,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,1,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,0,0,0,0}
        }
    }},

    // Reverse L Block
    {4, {
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,1,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,1,0},
            {0,1,1,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,1,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,0,0,0,0}
        }
    }},

    // Zig Block (S)
    {2, {
        {
            {0,0,0,0,0},
            {0,1,0,0,0},
            {0,1,1,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,1,1,0},
            {0,1,1,0,0},
            {0,0,0,0,0}
        }
    }},

    // Zag Block (Z)
    {2, {
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,1,1,0,0},
            {0,1,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,1,0,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        }
    }},

    // Square Block (O)
    {1, {
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,1,0,0},
            {0,1,1,0,0},
            {0,0,0,0,0}
        }
    }}
};

int board[HEIGHT][WIDTH];
int updateDelayCounter = 0;
int score = 0;
char gameOpen = 1;
// int current_x = WIDTH/2;
// int current_y = 0;

typedef struct{
    char shape;
    char rotation;
    int x;
    int y;

} piece;

piece myPiece = {.shape = 1, .rotation=1, .x = WIDTH/2, .y=0};

void initializeBoard();
void printBoard();
void updateBoard();
void clearRow(int row);
char fallCheck();
void initializePiece();
void drawPiece();
void removePiece();
void updatePiece();
char moveCheck(int x, int y, int rotation);

int main(int argc, char * argv[]){

    initializeBoard();
    printBoard();
    initializePiece();
    usleep(UPDATEDELAY);
    // drawPiece();

    while(gameOpen){
        

        if (_kbhit()) {             // check if a key is pressed
            char c = _getch();      // get char without waiting for Enter
            if (c == 'q'){
                gameOpen = 0;
                
            }
        }

        
        // drawPiece();
        if(moveCheck(0, 1, 0)){
            updatePiece();  
            printf("updated\n");  
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
    
    drawPiece();
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
    // int current_x = WIDTH/2;
    // int current_y = 0;
    myPiece.x = WIDTH/2;
    myPiece.y = 0;
}

void drawPiece(){
    for(int i = 0; i < 5; i++){
        for (int j = 0; j< 5; j++){
            if (shapes[myPiece.shape].view[myPiece.rotation][i][j] == 1){
                board[myPiece.y + i][myPiece.x + j] = 1;
            }
        }
    }
}

void removePiece(){
    for(int i = 0; i<5; i++){
        for (int j =0; j<5; j++){
            if (shapes[myPiece.shape].view[myPiece.rotation][i][j] == 1){
                board[myPiece.y + i][myPiece.x + j] = 0;
            }
        }
    }
}
void updatePiece(){

    removePiece();

    myPiece.y ++;
}

char moveCheck(int x, int y, int rotation){
    int temp_x = myPiece.x + x;
    int temp_y = myPiece.y + y;
    int temp_rotation = (myPiece.rotation + rotation) % shapes[myPiece.shape].rotations;
    
    piece tempPiece = {.shape = myPiece.shape, .x=temp_x, .y=temp_y, .rotation=temp_rotation};

    removePiece();

    for(int i =0; i<5; i++){
        for (int j = 0; j<5; j++){
            if(shapes[tempPiece.shape].view[tempPiece.rotation][i][j] == 1){
                int temp_board_y = tempPiece.y + i;
                int temp_board_x = tempPiece.x + j;

                

                if(temp_board_y < 0 || temp_board_y >= HEIGHT || temp_board_x < 0 || temp_board_x >= WIDTH || ((board[temp_board_y][temp_board_x] == 1))){
                    printf("collision at %d, %d\n", temp_board_x, temp_board_y);
                    drawPiece();
                    return 0;
                }

            }
        }
    }

    drawPiece();

    return 1;
}






