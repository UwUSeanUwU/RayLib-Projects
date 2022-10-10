#include <iostream>
#include <vector>
#include <raylib/raylib.h>


using namespace std;

class Player
{
private:
    Vector2 player_coordinates;
    bool blast;
    double time_spawned;
public:
    Player();
    void move(bool left, bool right, bool up, bool down);
    void update();
    ~Player();
};

Player::Player()
{
    player_coordinates = {400.0f, 300.0f};
}

void Player::move(bool left, bool right, bool up, bool down){
    if (left && right && up && down){

    }
    
    if(left && right)
    {
        if(up){

        }else if(down){

        }
    }

    else if(up && down){
        if(left){
            
        }else if(right){

        }
    }
    else(
        
    )
}

void Player::update(){
    DrawCircle(player_coordinates.x, player_coordinates.y, 1.0f, BLUE);
}

Player::~Player()
{
}


class Bullet
{
private:
    Vector2 bullet_coordinates;
public:
    Bullet();
    ~Bullet();
};

Bullet::Bullet(/* args */)
{
}

Bullet::~Bullet()
{
}


int main() {
    InitWindow(800, 600, "Pew Pew Pew");
    Player player;

    while (!WindowShouldClose()) {
        BeginDrawing();
            player.update()
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

