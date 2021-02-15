#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<ctime>

using namespace std;


class Board{
    int height, width;
    vector<vector<int>> board;
    int numberOfDice;
    unordered_map<int, int> snakeMap;
    unordered_map<int, int> ladderMap;
    public:
    Board(){
        this->height = 10;
        this->width = 10;
        this->numberOfDice = 1;
        vector<vector<int>> t(height, vector<int>(width, 0));
        this->board = t;
    }
    Board(int height, int width){
        this->height = height;
        this->width = width;
        this->numberOfDice = 1;
        vector<vector<int>> t(height, vector<int>(width, 0));
        this->board = t;
    }

    int getHeight(){
        return this->height;
    }
    void setHeight(int height){
        this->height = height;
    }

    int getWidth(){
        return this->width;
    }
    void setWidth(int width){
        this->width = width;
    }

    int getNumberOfDice(){
        return this->numberOfDice;
    }
    void setNumberOfDice(int numberOfDice){
        this->numberOfDice = numberOfDice;
    }

    void addSnake(int tail, int head){
        this->snakeMap[head] = tail;
    }

    bool checkSnakeHead(int position){
        if(this->snakeMap.find(position)==snakeMap.end()){
            return false;
        }
        return true;
    }

    int getSnakeTail(int position){
        return this->snakeMap[position];
    }

    bool checkLadderTail(int position){
        if(this->ladderMap.find(position)==ladderMap.end()){
            return false;
        }
        return true;
    }

    int getLadderHead(int position){
        return this->ladderMap[position];
    }

    void addLadder(int tail, int head){
        this->ladderMap[tail] = head;
    }

};


class SnakeAndLadder{
    int numberOfPlayers;
    int numberOfDice;
    unordered_map<int,int> playerPosition;
    int currentPlayer;
    bool gameOver;
    public:
    SnakeAndLadder(){
        this->numberOfPlayers = 2;
        this->numberOfDice = 1;
        srand(time(0));
        for(int i=0;i<numberOfPlayers;++i){
            playerPosition[i] = 0;
        }
        this->currentPlayer=0;
        this->gameOver = false;
    }
    SnakeAndLadder(int numberOfPlayers, int numberOfDice){
        this->numberOfPlayers = numberOfPlayers;
        this->numberOfDice = numberOfDice;
        srand(time(0));
        for(int i=0;i<numberOfPlayers;++i){
            playerPosition[i] = 0;
        }
        this->currentPlayer=0;
        this->gameOver = false;
    }

    int getNumberOfPlayers(){
        return this->numberOfPlayers;
    }
    void setNumberOfPlayers(int numberOfPlayers){
        this->numberOfPlayers = numberOfPlayers;
    }

    int getNumberOfDice(){
        return this->numberOfDice;
    }
    void setNumberOfDice(int numberOfDice){
        this->numberOfDice = numberOfDice;
    }

    int rollDice(){
        return 1 + (rand()%(6*this->numberOfDice));
    }
    
    int getPlayerPosition(int player){
        return this->playerPosition[player];
    }
    void setPlayerPosition(int player, int position){
        this->playerPosition[player] = position;
    }
    
    int getCurrentPlayer(){
        return this->currentPlayer;
    }
    void setCurrentPlayer(int player){
        this->currentPlayer = player;
    }

    int getGameOver(){
        return this->gameOver;
    }
    void setGameOver(bool g){
        this->gameOver = g;
    }

    void foundWinner(Board &board, int player){
        cout<<"Player "<<player<<" has won!!"<<endl;
        this->gameOver = true;
    }

    void movePlayer(Board &board, int numberOnDice){
        int position = this->playerPosition[this->currentPlayer];
        int newPosition = position+numberOnDice;
        if( (position+numberOnDice) > 100){
            cout<<"Move goes out of board"<<endl;
        }
        else{
            
            if(board.checkSnakeHead(newPosition)){
                cout<<"eaten by snake"<<endl;
                newPosition = board.getSnakeTail(newPosition);
            }
            else if(board.checkLadderTail(newPosition)){
                cout<<"found a ladder"<<endl;   
                newPosition = board.getLadderHead(newPosition);
            }

            cout<<"Player "<<this->currentPlayer<<" rolled a "<<numberOnDice<<" and moved from "<<position<<" to "<<newPosition<<endl;
            setPlayerPosition(this->currentPlayer, newPosition);
            if(newPosition == (board.getHeight()*board.getWidth())){
                foundWinner(board, this->currentPlayer);
            }
            //this->playerPosition[this->currentPlayer] = position+numberOnDice;;
        }
        setCurrentPlayer( (this->currentPlayer+1)%numberOfPlayers);
    }

};  


int main(){
    Board board(10,10);
    
    board.addSnake(62, 5);
    board.addSnake(33, 6);
    board.addSnake(49, 9);
    board.addSnake(88, 16);
    board.addSnake(41, 20);
    board.addSnake(56, 53);
    board.addSnake(98,
     64);
    board.addSnake(93, 73);
    board.addSnake(95, 75);

    board.addLadder(2,37);
    board.addLadder(27,46);
    board.addLadder(10,32);
    board.addLadder(51,68);
    board.addLadder(61,79);
    board.addLadder(71,91);
    board.addLadder(81,100);
    SnakeAndLadder game;
    int diceValue;
    while(!game.getGameOver()){
        diceValue = game.rollDice();
        game.movePlayer(board, diceValue);
    }

    return 0;
}