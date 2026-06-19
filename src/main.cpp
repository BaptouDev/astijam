#include <raylib.h>
#include <utility>
#include <include/entity.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    vector<string> sm;
    animation dance_tan = {{0,1},{.2,.2},false};
    map<string,animation> tanim = {{"dance", dance_tan}};
    
    AnimatedEntity tan = AnimatedEntity(Vector2f(67,67), "tamere",sm , "res/img/test_tan.png", 
        6.0, 0.0, 64, 0, tanim, "dance");


    float dt = GetFrameTime();
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        BeginDrawing();

            ClearBackground(SKYBLUE);
            tan.draw(dt);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}