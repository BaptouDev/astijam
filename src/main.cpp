#include <raylib.h>
#include <utility>
#include <include/entity.h>
#include <include/player.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Player player = Player(Vector2f(0,0));
    Sprite map = Sprite("res/maps/test2/simplified/Level_0/_composite.png",Vector2f(0,0),4.0,0.0,Vector2f(0,0),720*752,0);

    Vector2f camera_pos;

    float dt = GetFrameTime();
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();

        player.update(dt,Vector2f(GetMousePosition().x,GetMousePosition().y)+camera_pos);
        camera_pos = player.sprite.origin + player.body.position -Vector2f(screenWidth,screenHeight)*(.5);
        BeginDrawing();
            ClearBackground(SKYBLUE);
            //tan.draw(dt);
            map.draw(dt,camera_pos);
            player.draw(dt,camera_pos);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}