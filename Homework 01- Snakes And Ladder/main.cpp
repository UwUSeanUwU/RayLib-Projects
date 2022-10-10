#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Board
{
private:
    vector<int> board;
public:
    Board(vector<int> board);
    Board();
    void setUpBoard(int single_int);
    int getTileValue(int tile_number);
    int getBoardSize();
    void deleteBoard();
    ~Board();
};

Board::Board(vector<int> board)
{
    this->board = board;
}

Board::Board(){}

void Board::setUpBoard(int single_int){
    board.push_back(single_int);
}

int Board::getTileValue(int tile_number){
    return board[tile_number];
}

int Board::getBoardSize(){
    return board.size();
}

void Board::deleteBoard(){
    while (!board.empty())
    {
        board.pop_back();
    }  
}

Board::~Board()
{
}

class Player
{
private:
    int player_number;
    int current_position;
public:
    Player(int player_number);
    int getCurrentPosition();
    int roll(int player_input);
    void playerMove(int dice_result);
    string playerTurn();
    string playerResult(int dice_result, int tile);
    bool isFinished();
    ~Player();
};

Player::Player(int player_number)
{
    this->player_number = player_number;
    current_position = 0;
}

int Player::getCurrentPosition(){
    return current_position;
}

void Player::playerMove(int dice_result){
    current_position += dice_result;
}

string Player::playerTurn(){
    string message;
    message = "Player " + to_string(player_number) + "'s turn.\n"
            + "Current cell position: " + to_string(current_position) + "\n"
            + "please pick a number from 1 to 1000: ";
    return message;
}

string Player::playerResult(int dice_result, int tile){
    string message  = "Dice roll: " + to_string(dice_result) + "\n"
                    + "You landed on Cell " + to_string(current_position) + "\n";
    
    if (current_position < 100) playerMove(tile);

    if (tile < 0){
        message += "You landed on snake you moved " + to_string(tile) + " tiles back.\n"
                +  "You are now on tile " + to_string(current_position) + "\n";
    }
    else if (tile > 0){
        message += "You landed on a ladder tile you moved " + to_string(tile) + " tiles forward.\n"
                +  "You are now on tile " + to_string(current_position) + ".\n";
    }
    else if (current_position >= 99){
        message += ":3\n";
    }
    else{
        message += "You landed on a regular tile.\nNothing happens...\n";
    }
    message += "----------\n";
    return message; 
}

int Player::roll(int player_input){
    int result;
    if (player_input < 1 || player_input > 1000){
        return -1;
    }

    srand(time(0));
    int random_number = rand() % 100 + 1;
    result = 1 + (((player_input + random_number + 1) / 2 * 10 + 41) % 6);
    if (result == 0){
        result = 6;
    }

    return result;
}

bool Player::isFinished(){
    if(current_position >= 99){
        string message = "Congratulations Player " + to_string(player_number) + ".\n"
                       + "You win!\n";
        cout << message;
        return true;
    }
    else return false;
}

Player::~Player()
{
}

int main(){
    int tmp;
    int dice_result;
    int turn = 0;
    int player_input;
    int number_of_players = 1;
    int tile_info;
    bool completed = false;
    vector<Player *> players;
    vector<int> board_input;
    ifstream file;
    file.open("board.txt");
    if (!file){
        cout << "Unable to open file" << endl;
        exit(1); // terminate with error
    }
    while(!file.eof()){
        file >> tmp;
        board_input.push_back(tmp);
    }
    file.close();
    Board board(board_input);
    
    while (number_of_players < 2 || number_of_players > 4)
    {
        cout << "Please input the number of players(2-4 players)\n";
        cin >> number_of_players;
    }
    
    
    for(int player_number = 1; player_number <= number_of_players; player_number++){
        players.push_back(new Player(player_number));
    }

    cout << "----------\n";
    
    while (!completed)
    {
        cout << players[turn]->playerTurn();
        cin >> player_input;
        dice_result = players[turn]->roll(player_input);
        if (dice_result == -1){
            while (dice_result == -1)
            {
                cout << "Please input a value from 1 to 1000: ";
                cin >> player_input;
                dice_result = players[turn]->roll(player_input);
            }
        }
        players[turn]->playerMove(dice_result);
        tile_info = board.getTileValue(players[turn]->getCurrentPosition());
        cout << players[turn]->playerResult(dice_result, tile_info);

        if(players[turn]->isFinished()){
            completed = true;
        }
        
        turn++;
        if (turn >= number_of_players){
            turn = 0;
        }
    }
    return 0;
}
