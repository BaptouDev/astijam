#include <raylib.h>
#include <utility>

#include <include/entity.h>
#include <include/player.h>
#include <include/enemy.h>
#include <include/json.hpp>
#include <fstream>
#include <sstream>
#include <include/flyingenemy.h>

using namespace std;
using json = nlohmann::json;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Player player = Player(Vector2f(128,128));
    Sprite sprite_map = Sprite("res/maps/test2/simplified/Level_0/_composite.png",Vector2f(0,0),4.0,0.0,Vector2f(0,0),720*752,0);

    vector<PhysicsBody> map1col;
    vector<PhysicsBody> bridgescol;
    vector<vector<int>> int_map1;
    vector<vector<int>> intbridges;

    ifstream file("res/maps/test2/simplified/Level_0/Tiles1Layer.csv");
    string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<int> row;
        while (std::getline(ss, field, ',')) {
            row.push_back(stoi(field));
        }
        int_map1.push_back(row);
    }
    ifstream file2("res/maps/test2/simplified/Level_0/Pont.csv");
    string line2;
    while (std::getline(file2, line2)) {
        std::stringstream ss(line2);
        std::string field;
        std::vector<int> row;
        while (std::getline(ss, field, ',')) {
            row.push_back(stoi(field));
        }
        intbridges.push_back(row);
    }
    for(int i=1;i<int_map1.size()-1;i++){
        for(int j=1;j<int_map1.size()-1;j++){
            if((int_map1[i][j] == 0)/*&&(int_map1[i-1][j]==1||int_map1[i-1][j-1]==1
            ||int_map1[i][j-1]==1||int_map1[i+1][j-1]==1||int_map1[i+1][j]==1
            ||int_map1[i+1][j+1]==1||int_map1[i][j+1]==1||int_map1[i-1][j+1]==1)*/){
                if(intbridges[i][j]==1){
                    bridgescol.push_back(PhysicsBody(Vector2f(j*16*4.0,i*16*4.0),Vector2f(64.0,64.0),Vector2f(0,0),{}));
                }
                else{
                    map1col.push_back(PhysicsBody(Vector2f(j*16*4.0,i*16*4.0),Vector2f(64.0,64.0),Vector2f(0,0),{}));
                }
            }
        }
    }

    ifstream entities_file("res/maps/test2/simplified/Level_0/data.json");
    json data_file;
    entities_file>>data_file;
    map<int,vector<AnimatedEntity*>> enemies;

    auto paff = data_file["entities"]["DinoEnemy1"].get<vector<json>>();
    for(auto i : paff){
        enemies[0].push_back(new Enemy(Vector2f(i["x"].get<float>(),i["y"].get<float>())));
    }

    Enemy enemy = Enemy(Vector2f(67,67));

    FlyingEnemy fenemy = FlyingEnemy(Vector2f(360,360));

    float dt = GetFrameTime();
    Vector2f camera_pos;
    SetTargetFPS(60);
    player.get_col_list(map1col);
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        player.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos);
        enemy.get_player_pos(player.body.position);
        enemy.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );
        fenemy.get_player_pos(player.body.position);
        fenemy.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );
        camera_pos = player.sprite.origin + player.body.position -Vector2f(screenWidth,screenHeight)*(.5);
        BeginDrawing();
            ClearBackground(SKYBLUE);
            
            //tan.draw(dt);
            sprite_map.draw(dt,camera_pos);
            for (auto i : map1col){
                DrawRectangle(i.position.x-camera_pos.x,i.position.y-camera_pos.y,i.collision_rect.height,i.collision_rect.width,GREEN);
            }
            player.draw(dt,camera_pos);
            enemy.draw(dt,camera_pos);
            fenemy.draw(dt,camera_pos);
            DrawRectangle(player.body.collision_rect.x-camera_pos.x,player.body.collision_rect.y-camera_pos.y,player.body.collision_rect.width,player.body.collision_rect.height,GREEN);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}