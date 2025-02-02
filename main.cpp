#include <iostream>

#include "board.h"

#include "raylib.h"

#define screenWidth 1000
#define screenHeight 1000
#define squareWidth 125

using namespace std;

int main() {
    InitWindow(screenWidth, screenHeight, "Chessmate");

    SetTargetFPS(60);

    Board board;

    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawText("Hello, Chessmate!", 190, 200, 20, BLACK);

        for(int idx = 1; idx <= 8; idx++) {
            for(char ch = 'a'; ch <= 'h'; ch++) {
                Square square = board.board[ch][idx];
                DrawRectangle(square.x, square.y, squareWidth, squareWidth, square.color);
                DrawTexture(square.piece.image, square.x, square.y, WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
