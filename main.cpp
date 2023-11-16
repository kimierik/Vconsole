
#include "raylib.h"
#include "src/console/console.h"

int main(){

    InitWindow( 800, 800, "wins");

    VConsole *console=VConsole::getConsole();

    //this is a var that we are changeing and printing
    int testvaruable=0;

    console->exposeVariable("TEST", &testvaruable, intiger);
    

    while (!WindowShouldClose()) {
        console->update();
        BeginDrawing();

        ClearBackground(WHITE);
        console->drawinput();

        EndDrawing();
    }


    CloseWindow();

}
