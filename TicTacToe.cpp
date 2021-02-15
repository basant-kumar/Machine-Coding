#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<sstream>

using namespace std;

class TicTacToe{
    int n=3, m=3;
    vector<vector<int>> board;
    int player;
    bool empty;

    public:

    TicTacToe(){
        this->player = 1;
        this->empty = false;
        for(int i=0;i<3;++i){
            vector<int> t;
            for(int j=0;j<3;++j){
                t.push_back(0);
            }
            this->board.push_back(t);
            t.clear();
        }
        //board(3, vector<int>(3));
    }

    void setValue(int x, int y, int val){
        this->board[x][y] = val;
    }

    vector<vector<int>> getBoard(){
        return this->board;
    } 
    void setBoard(vector<vector<int>> board){
        this->board = board;
    }

    int getPlayer(){
        return this->player;
    }
    void setPlayer(int player){
        this->player = player;
    }

    bool isEmpty(){
        return this->empty;
    }
    void setEmpty(bool empty){
        this->empty = empty;
    }

    

};

class Service{
    public:

    void printBoard(TicTacToe &t){
        t.setEmpty(false);
        cout<<"-----------------------------"<<endl;
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                if(t.getBoard()[i][j]==1){
                    cout<<" X ";
                }
                else if(t.getBoard()[i][j]==-1){
                    cout<<" O ";
                }
                else{
                    cout<<"   ";
                    t.setEmpty(true);
                }
            }cout<<endl;
        }cout<<endl;
        cout<<"-----------------------------"<<endl;

    }

    void fillPlace(TicTacToe &t, int x, int y){
        if(x<0 || x>3 || y<0 || y>3){
            cout<<"Please enter valid position"<<endl;
            return;
        }
        if(t.getBoard()[x][y]!=0){
            cout<<"position is not empty"<<endl;
            return;
        }
        //t.getBoard()[x][y] = t.getPlayer();
        t.setValue(x,y, t.getPlayer());
        //cout<<"player changed "<<-t.getPlayer()<<endl;
        t.setPlayer(-(t.getPlayer()));
        //printBoard(t);
        //cout<<t.getPlayer()<<endl;
    }

    bool isWin(TicTacToe t, int player){
        return ((t.getBoard()[0][0] + t.getBoard()[0][1] + t.getBoard()[0][2]) == 3*player) ||
                ((t.getBoard()[1][0] + t.getBoard()[1][1] + t.getBoard()[1][2]) == 3*player) ||
                ((t.getBoard()[2][0] + t.getBoard()[2][1] + t.getBoard()[2][2]) == 3*player) ||
                ((t.getBoard()[0][0] + t.getBoard()[1][0] + t.getBoard()[2][0]) == 3*player) ||
                ((t.getBoard()[0][1] + t.getBoard()[1][1] + t.getBoard()[2][1]) == 3*player) ||
                ((t.getBoard()[0][2] + t.getBoard()[1][2] + t.getBoard()[2][2]) == 3*player) ||
                ((t.getBoard()[0][0] + t.getBoard()[1][1] + t.getBoard()[2][2]) == 3*player) ||
                ((t.getBoard()[2][0] + t.getBoard()[1][1] + t.getBoard()[0][2]) == 3*player);
    }

    void displayWinner(TicTacToe &t){
        if(isWin(t, 1)){
            cout<<"X wins"<<endl;
            t.setEmpty(false);
        }
        else if(isWin(t, -1)){
            cout<<"O wins"<<endl;
            t.setEmpty(false);
        }
        else{
            if(!t.isEmpty()){
                cout<<"it's tie"<<endl;
            }
        }
    }

    

};


int main(){

    TicTacToe t;
    Service s;
    cout<<"Game is starting........"<<endl;
    int x,y;
    do{
        if(t.getPlayer()==1){
            cout<<"Player X turn"<<endl;
        }
        else{
            cout<<"Player O turn"<<endl;
        }
        cout<<"Enter X and Y positions"<<endl;
        cin>>x>>y;
        
        s.fillPlace(t, x, y);
        s.printBoard(t);
        s.displayWinner(t);

    }while(t.isEmpty());

    return 0;
}