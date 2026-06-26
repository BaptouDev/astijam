#include <raylib.h>
#include <utility>

#include <include/entity.h>
#include <include/player.h>
#include <include/enemy.h>
#include <include/json.hpp>
#include <fstream>
#include <iostream>
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
            if((int_map1[i][j] == 0)){
                if(intbridges[i][j]==1){
                    bridgescol.push_back(PhysicsBody(Vector2f(j*16*4.0,i*16*4.0),Vector2f(64.0,64.0),Vector2f(0,0),{}));
                }
                else{
                    map1col.push_back(PhysicsBody(Vector2f(j*16*4.0,i*16*4.0),Vector2f(64.0,64.0),Vector2f(0,0),{}));
                }
            }
        }
    }
    vector<PhysicsBody> full_col;
    full_col.reserve(bridgescol.size() + map1col.size());
    std::copy(bridgescol.begin(), bridgescol.end(), std::back_inserter(full_col));
    std::copy(map1col.begin(), map1col.end(), std::back_inserter(full_col));

    vector<PhysicsBody> current_col = map1col;

    vector<AnimatedEntity*> current_enemies;
    vector<Fireball> fireballs;

    ifstream entities_file("res/maps/test2/simplified/Level_0/data.json");
    json data_file;
    entities_file>>data_file;
    map<int,vector<AnimatedEntity*>> enemies;
    map<int,AreaRect> bridges;

    auto dino_enemy1_file = data_file["entities"]["DinoEnemy1"].get<vector<json>>();
    for(auto i : dino_enemy1_file){
        enemies[i["customFields"]["room"].get<int>()].push_back(new Enemy(Vector2f(i["x"].get<float>()*4.0,i["y"].get<float>()*4.0)));
    }

    auto dino_enemy2_file = data_file["entities"]["DinoEnemy2"].get<vector<json>>();
    for(auto i : dino_enemy2_file){
        enemies[i["customFields"]["room"].get<int>()].push_back(new FlyingEnemy(Vector2f(i["x"].get<float>()*4.0,i["y"].get<float>()*4.0)));
    }

    auto bridge_file = data_file["entities"]["Bridge"].get<vector<json>>();
    for(auto i : bridge_file){
        bridges[i["customFields"]["room"].get<int>()] = AreaRect(Vector2f(i["x"].get<float>()*4.0,i["y"].get<float>()*4.0),Vector2f(64,64),Vector2f(0,0));
    }


    int room_counter=0;

    bool is_fighting = false;
    //Enemy enemy = Enemy(Vector2f(67,67));

    //FlyingEnemy fenemy = FlyingEnemy(Vector2f(360,360));
    //Boss boss = Boss(Vector2f(72,72));


    Sound pizza;
    Sound gameover;
    Sound successfloor;
    Sound jungleambiance;
    Sound hitsound;
    Sound enemibeatup;
    Sound boulefire;
    Music music;

    

   // InitAudioDevice();
   
    pizza= LoadSound("res/audio/eatpizza.wav");
    gameover = LoadSound("res/audio/gameoverpertedepv.wav");
    successfloor = LoadSound("res/audio/successfloor.wav");
    hitsound = LoadSound("res/audio/hitsound.wav");
    boulefire = LoadSound("res/audio/jungleambiance.wav");
    jungleambiance = LoadSound("res/audio/eatpizza.wav");
    enemibeatup = LoadSound("res/audio/enemigetbeatup.wav");

    music = LoadMusicStream("res/audio/song2.wav");

    PlayMusicStream(music);
    

    float dt = GetFrameTime();
    Vector2f camera_pos;
    SetTargetFPS(60);
    player.get_col_list(map1col);
    while (!WindowShouldClose())
    {

        UpdateMusicStream(music);
  

  

        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            PlaySound(hitsound);
        }
        


        dt = GetFrameTime();
        player.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos);
        for(auto i : current_enemies){
            i->update(dt,player.body.position);
        }
        /*enemy.get_player_pos(player.body.position);
        enemy.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );
        fenemy.get_player_pos(player.body.position);
        fenemy.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );*/

        //boss.get_player_pos(player.body.position);
        //boss.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y) );
        camera_pos = player.sprite.origin + player.body.position -Vector2f(screenWidth,screenHeight)*(.5);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2f relative_mouse_pos = player.body.position + player.sprite.origin - (Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos);
            if (player.fireball_cd<0){
                player.fireball_cd = player.fireball_intervall;
                float mouse_angle = atan2(relative_mouse_pos.y,relative_mouse_pos.x);
                Fireball ball = Fireball(player.body.position + player.sprite.origin*.5+ Vector2f(-cos(mouse_angle),-sin(mouse_angle))*64.0, RAD2DEG*mouse_angle,200.0, (Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos-player.body.position).normalized());
                fireballs.push_back(ball);
            }
            
        }

        for (auto&i : fireballs) {
            i.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos);
            for (auto j : current_enemies){
                if(CheckCollisionCircleRec((i.sprite.origin+i.position).to_rayvect2(),i.radius,{j->position.x, j->position.y, 32.0*4.0,32.0*4.0})){
                    j->damage(50);
                    i.life_timer = -67.0;
                    break;
                }
            }
        }
        for (auto i = current_enemies.begin(); i != current_enemies.end(); ) {
            if ((*i)->is_dead()) {
                delete *i;
                i=current_enemies.erase(i);
            } else {
                ++i;
            }
        }

        for (auto i = fireballs.begin(); i != fireballs.end(); ) {
            if (i->life_timer<0) {
                i = fireballs.erase(i);
            } else {
            ++i;
            }
        }

        if(CheckCollisionRecs(player.body.collision_rect,bridges[room_counter].collision_rect)){
            for(auto i : enemies[room_counter]){
                current_enemies.push_back(i);
            }
            is_fighting = true;
            //player.get_col_list(full_col);
            room_counter++;
            cout<<"lessgo"<<endl;
        }
        if(is_fighting&&current_enemies.empty()){
            player.get_col_list(map1col);
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);
            
            //tan.draw(dt);
            sprite_map.draw(dt,camera_pos);
            /*for (auto i : map1col){
                DrawRectangle(i.position.x-camera_pos.x,i.position.y-camera_pos.y,i.collision_rect.height,i.collision_rect.width,GREEN);
            }*/
            /*for(auto i: bridges){
                DrawRectangle(i.second.collision_rect.x-camera_pos.x,i.second.collision_rect.y-camera_pos.y,i.second.collision_rect.height,i.second.collision_rect.width,GREEN);
            }*/
            player.draw(dt,camera_pos);
            for(auto i : current_enemies){
                i->draw(dt,camera_pos);
            }
            for (auto i : fireballs){
                i.draw(dt,camera_pos);
            }
        
            /*enemy.draw(dt,camera_pos);
            fenemy.draw(dt,camera_pos);*/
            //DrawRectangle(player.body.collision_rect.x-camera_pos.x,player.body.collision_rect.y-camera_pos.y,player.body.collision_rect.width,player.body.collision_rect.height,GREEN);
            //boss.draw(dt,camera_pos);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}