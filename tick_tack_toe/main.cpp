#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
vector<vector<char>> game(3, vector<char>(3, '.'));

bool checkIfGameOver(){

//check all rows
    int j = 0;
    for(int i = 0; i < 3; i++){
        if((game[i][j] != '.') && ( (game[i][j] == game[i][j+1]) &&( game[i][j+1] == game[i][j+2]))){
            return true;
        }
    }

//check all colms
    int i1 = 0;
    for(int j1 = 0; j1 < 3; j1++){
        if((game[i1][j1] != '.') && ((game[i1][j1] == game[i1+1][j1]) &&(game[i1+1][j1] == game[i1+2][j1]))){
            return true;
        }
    }

//check diagonally
    int m = 1;
    int n = 1;
    if((game[m][n] != '.') && ((game[m][n] == game[m-1][n-1]) && (game[m-1][n-1] == game[m+1][n+1]))){
        return true;
    }
    if((game[m][n] != '.') && ((game[m][n] == game[m-1][n+1]) &&(game[m-1][n+1] == game[m+1][n-1]))){
        return true;
    }
    return false;
}

void displayGame(){
cout<<endl;
cout<<"       GAME       "<<endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout<<"   "<<game[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

pair<int,int> mapInputToIndex(int n){

pair<int, int> index;
int i, j;

switch(n){

    case(1):
            i = 0;
            j = 0;
            break;
    case(2):
            i = 0;
            j = 1;
            break;
    case(3):
            i = 0;
            j = 2;
            break;
    case(4):
            i = 1;
            j = 0;
            break;
    case(5):
            i = 1;
            j = 1;
            break;
    case(6):
            i = 1;
            j = 2;
            break;
    case(7):
            i = 2;
            j = 0;
            break;
    case(8):
            i = 2;
            j = 1;
            break;
    case(9):
            i = 2;
            j = 2;
            break;
    default:
            i = 0;
            j = 0;
            break;
}

index.first = i;
index.second = j;
return index;

}

bool playGame(int spot, char symbol){
    pair<int, int> index = mapInputToIndex(spot);

    //cout<<"Mapped cooredinates, row : "<< index.first <<" col: "<< index.second <<endl;

    int i = index.first;
    int j = index.second;

    if(game[i][j] == '.'){
        game[i][j] = symbol;
    }
    else{
        cout<<"spot already filled, chose another! "<<endl;
    }
    displayGame();
    if(checkIfGameOver() == true){
        cout<<"    YOU WIN!!    "<<endl <<endl;
        return true;
    }
    return false;
}

bool computerTurn(char symbol){

    cout<<" COMPUTER TURN, symbol: "<< symbol <<endl;
    int spot = rand() % 9;
    pair<int, int> index = mapInputToIndex(spot);
    int i = index.first;
    int j = index.second;

    while(game[i][j] != '.'){

        spot = rand() % 9;
        index = mapInputToIndex(spot);
        i = index.first;
        j = index.second;
    }

    game[i][j] = symbol;
    displayGame();
    if(checkIfGameOver() == true){
        cout<<"    COMPUTER WINS!    "<<endl <<endl;
        return true;
    }
    return false;
}

int main(){

    cout<<"             TIC TAC TOE             "<<endl<<endl;

    char symbol = 'm';
    char symbol_comp;
    cout<<" Choose either o or x "<<endl;

    while(1){
        if(symbol == 'x' || symbol == 'o'){ break;}
        cin>>symbol;
        cout<<"choose either o or x!  "<<endl;
    }
    cout<<" You chose: " <<symbol <<endl;

    if(symbol == 'x'){
        symbol_comp = 'o';
    }
    else{
        symbol_comp = 'x';
    }


    displayGame();

    bool playerg = false;
    bool compg = false;

    while(checkIfGameOver() == false){
        int spot;
        cout<<"Chose spot (1-9) "<<endl;
        cin>>spot;

        playerg = playGame(spot, symbol);
        if( (playerg == true) || (checkIfGameOver() == true)){
            cout<<"************GAME OVER***************"<<endl;
            break;
        }

        compg = computerTurn(symbol_comp);
        if( (compg == true) || (checkIfGameOver() == true)){
            cout<<"************GAME OVER***************"<<endl;
            break;
        }
    }

    return 0;
}