#include <iostream>
#include <ctime>

int *createBoard (){

    int *board {new int [9]};

    for (int x{0}; x < 9; ++x){
        board [x] = 0;
    }

    return board;

}

bool calc ( int *board, std::size_t x, std::size_t y, int inc){

    std::size_t loc {y*3 + x};

    if ((board [loc] == 2) || (board [loc] == 1)){
        return false;
    }
    else {
        board [loc] = inc;
        return true;
    }

}

void printBoard ( int *board ){

    for (int z{0}; z < 9; ++z){

        std::string r {};

        if (board [z] == 0){
            r = "  ";
        }
        else if (board [z] == 1){
            r = " X";
        }
        else {
            r = " O";
        }

        std::cout<<r;

        if ((z%3 == 0) || (z%3 == 1)){
            std::cout<<" |";
        }
        else {
            std::cout<<std::endl;
            if (z != 8){
                std::cout<<"___________";
            }
            std::cout<<std::endl;
        }

    }

}

int won (int *board){

    if ((board [0] != 0) && (board [0] == board [1]) && (board [1] == board [2])){
        if (board [0] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [3] != 0) && (board [3] == board [4]) && (board [4] == board [5])){
        if (board [3] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [6] != 0) && (board [6] == board [7]) && (board [7] == board [8])){
        if (board [6] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [1] != 0) && (board [1] == board [4]) && (board [4] == board [7])){
        if (board [1] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [2] != 0) && (board [2] == board [5]) && (board [5] == board [8])){
        if (board [5] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [0] != 0) && (board [0] == board [3]) && (board [3] == board [6])){
        if (board [0] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [0] != 0) && (board [4] == board [0]) && (board [4] == board [8])){
        if (board [0] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    if ((board [2] != 0) && (board [2] == board [4]) && (board [4] == board [6])){
        if (board [2] == 2){
            return 2;
        }
        else {
            return 1;
        }
    }

    return 0;

}

int compMove ( int moves [], int &justincase) {

    int mov [9] {0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (int x{0}; x < 9; ++x){
        for (int y{0}; y < 9; ++y){
            if (moves [x] == mov [y]){
                mov [y] = 9;
            }
        }
    }

    int leng {0};

    int Guess [8] {};

    for (int p{0}; p < 9; ++p){
        if (mov [p] != 9){
            Guess [leng] = mov [p];
            ++leng;
        }
    }
    
    srand(time(0));
    int compMve {rand()%(9 - leng)};

    justincase = Guess [1];

    return Guess [compMve];

}

void delBoard (int *board){

    delete [] board;
    board = nullptr;

}

bool Draw (int *board){

    for (int c{0}; c < 9; ++c){
        if (board [c] == 0){
            return false;
        }
    }

    return true;

}

int main() {
    
    int moves [9] {10,10,10,10,10,10,10};

    int *board {createBoard()};

    int m{0};

    while ((won(board) == 0) && (Draw(board) == false)){

        int justincase {0};

        printBoard(board);

        std::size_t xValue {};
        std::size_t yValue {};

        std::cout<<"What is the x value of your space? ";
        std::cin>>xValue;

        std::cout<<"What is the y value of your space? ";
        std::cin>>yValue;
        std::cout<<std::endl;

        if (!calc(board, xValue, yValue, 1)){
            std::cout<<"That space is already marked!";
            std::cout<<std::endl;
        }
        else {
            moves[m] = yValue*3 + xValue;
            ++m;
        }

        if (m == 8){
            break;
        }

        int comp {compMove(moves, justincase)};
        if (m != 1 && compMove(moves, justincase) == 0){
          comp = justincase;
        }
        int compY {comp/3};
        int compX {comp%3};

        if (!calc(board, compX, compY, 2)){
            comp = compMove(moves, justincase);
        }
        else{
          moves [m] = comp;
          ++m;
        }

    }

    std::cout<<std::endl;
    printBoard(board);

    if (won(board) == 1){
        std::cout<<"You Won! Congratulations!";
    }
    else if (won(board) == 2){
        std::cout<<"You lost. Better luck next time.";
    }

    else if (Draw(board)){
        std::cout<<"The match is a draw.";
    }

    delBoard(board);

    return 0;
}