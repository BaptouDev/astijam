#include <raylib.h>
#include <utility>
#include <include/entity.h>
#include <include/player.h>
#include <include/enemy.h>
#include <include/json.hpp>
#include <fstream>
#include <sstream>
#include <include/flyingenemy.h>
#include <include/boss.h>

using namespace std;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Player player = Player(Vector2f(0,0));
    Sprite map = Sprite("res/maps/test2/simplified/Level_0/_composite.png",Vector2f(0,0),4.0,0.0,Vector2f(0,0),720*752,0);

    vector<PhysicsBody> map1col;

    ifstream file("res/maps/test2/simplified/Level_0/Tiles1Layer.csv");
    string line;
    vector<vector<int>> int_map1;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<int> row;
        while (std::getline(ss, field, ',')) {
            row.push_back(stoi(field));
        }
        int_map1.push_back(row);
    }
    for(int i=1;i<int_map1.size()-1;i++){
        for(int j=1;j<int_map1.size()-1;j++){
            if((int_map1[i][j] == 0)&&(int_map1[i-1][j]==1||int_map1[i-1][j-1]==1
            ||int_map1[i][j-1]==1||int_map1[i+1][j-1]==1||int_map1[i+1][j]==1
            ||int_map1[i+1][j+1]==1||int_map1[i][j+1]==1||int_map1[i-1][j+1]==1)){
                
            }
        }
    }
    //ennemis
    Enemy enemy = Enemy(Vector2f(67,67));
    FlyingEnemy fenemy = FlyingEnemy(Vector2f(360,360));
    Boss boss = Boss(Vector2f(720,720));

    float dt = GetFrameTime();
    Vector2f camera_pos;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        player.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos);
        enemy.get_player_pos(player.body.position);
        enemy.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );
        fenemy.get_player_pos(player.body.position);
        fenemy.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );

        boss.get_player_pos(player.body.position);
        boss.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );

        BeginDrawing();

        camera_pos = player.sprite.origin + player.body.position -Vector2f(screenWidth,screenHeight)*(.5);
        BeginDrawing();
            ClearBackground(SKYBLUE);
            //tan.draw(dt);
            map.draw(dt,camera_pos);
            player.draw(dt,camera_pos);
            enemy.draw(dt,camera_pos);
            fenemy.draw(dt,camera_pos);
            boss.draw(dt,camera_pos);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}