#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 10
#define HEIGHT 20
#define UPDATEDELAY 300 // milliseconds

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

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

    // S Block
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

    // Z Block
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

    // O Block
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
int score = 0;
char gameOpen = 1;

typedef struct{
    char shape;
    char rotation;
    int x;
    int y;
} piece;

piece myPiece = {.shape = 0, .rotation = 0, .x = WIDTH/2, .y = 0};

// Function prototypes
void initializeBoard();
void printBoard();
void updateBoard();
void clearRow(int row);
char moveCheck(int x, int y, int rotation);
char movePiece(int x, int y, int rotation);
void initializePiece();

int main(){

    initializeBoard();
    initializePiece();

    while(gameOpen){

        if(_kbhit()){
            char c = _getch();
            if(c == 0 || c == -32) c = _getch(); // handle arrow keys

            switch(c){
                case 'q': gameOpen = 0; break;
                case UP: movePiece(0, 0, 1); break;
                case DOWN: movePiece(0, 1, 0); break;
                case LEFT: movePiece(-1, 0, 0); break;
                case RIGHT: movePiece(1, 0, 0); break;
                case SPACE: while(movePiece(0,1,0)); break; // hard drop
            }
        }

        // automatically move piece down
        if(moveCheck(0, 1, 0)){
            myPiece.y++;
        } else {
            // piece landed → fix it on board
            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    if(shapes[myPiece.shape].view[myPiece.rotation][i][j]){
                        int y = myPiece.y + i;
                        int x = myPiece.x + j;
                        if(y>=0 && y<HEIGHT && x>=0 && x<WIDTH){
                            board[y][x] = 1;
                        }
                    }
                }
            }
            // clear lines
            updateBoard();
            // new piece
            initializePiece();
            if(!moveCheck(0,0,0)){
                gameOpen = 0; // game over
            }
        }

        printBoard();
        Sleep(UPDATEDELAY);
    }

    printf("Game Over!\n");
    return 0;
}

void initializeBoard(){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            board[i][j] = 0;
        }
    }
}

void initializePiece(){
    myPiece.shape = rand() % 7;
    myPiece.rotation = 0;
    myPiece.x = WIDTH/2 - 2;
    myPiece.y = 0;
}

void printBoard(){
    printf("\033[H\033[J"); // clear terminal

    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            char cell = board[i][j];

            // Overlay current piece
            int relY = i - myPiece.y;
            int relX = j - myPiece.x;
            if(relY >=0 && relY <5 && relX >=0 && relX <5){
                if(shapes[myPiece.shape].view[myPiece.rotation][relY][relX] == 1){
                    cell = 1;
                }
            }

            if(cell) printf("|%c%c", 219, 219);
            else printf("|  ");
        }
        printf("|\n");
    }
    printf("\nScore: %d\n", score);
}

char moveCheck(int x, int y, int rotation){
    int tempX = myPiece.x + x;
    int tempY = myPiece.y + y;
    int tempRot = (myPiece.rotation + rotation) % shapes[myPiece.shape].rotations;

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(shapes[myPiece.shape].view[tempRot][i][j]){
                int boardX = tempX + j;
                int boardY = tempY + i;

                if(boardX<0 || boardX>=WIDTH || boardY<0 || boardY>=HEIGHT) return 0;
                if(board[boardY][boardX]) return 0;
            }
        }
    }

    return 1;
}

char movePiece(int x, int y, int rotation){
    if(moveCheck(x,y,rotation)){
        myPiece.x += x;
        myPiece.y += y;
        myPiece.rotation = (myPiece.rotation + rotation) % shapes[myPiece.shape].rotations;
        return 1;
    }
    return 0;
}

void clearRow(int row){
    for(int i=row;i>0;i--){
        for(int j=0;j<WIDTH;j++){
            board[i][j] = board[i-1][j];
        }
    }
    for(int j=0;j<WIDTH;j++) board[0][j] = 0;
}

void updateBoard(){
    int cleared = 0;
    for(int i=HEIGHT-1;i>=0;i--){
        char full = 1;
        for(int j=0;j<WIDTH;j++){
            if(board[i][j] == 0) full = 0;
        }
        if(full){
            cleared++;
            clearRow(i);
            i++; // recheck same row after shift
        }
    }
    score += cleared*100;
}
