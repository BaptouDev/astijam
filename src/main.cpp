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


    float dt = GetFrameTime();
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        player.update(dt);
        BeginDrawing();

            ClearBackground(SKYBLUE);
            //tan.draw(dt);
            player.draw(dt);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}