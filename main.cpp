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

    int file;
    int rank;
    Texture2D temp;

    Texture2D empty;

    while (!WindowShouldClose()) {
        BeginDrawing();

        int x = GetMousePosition().x;
        int y = GetMousePosition().y;


        for(int idx = 1; idx <= 8; idx++) {
            for(char ch = 'a'; ch <= 'h'; ch++) {
                Square square = board.board[ch][idx];

                if (x >= square.x && x <= (square.x+125) && y >= square.y && y <= (square.y+125)) {
                    file = square.file;
                    rank = square.rank;
                }

                DrawRectangle(square.x, square.y, squareWidth, squareWidth, square.color);
                DrawTexture(square.piece.image, square.x, square.y, WHITE);
            }
        }

        if (IsMouseButtonPressed(0)) {
            temp = board.board[file][rank].piece.image;
            board.board[file][rank].piece.image = empty;
        }

        // implement drag and drop
        if (IsMouseButtonDown(0)) {
            DrawTexture(temp, x-60, y-60, WHITE);
        }

        if (IsMouseButtonReleased(0)) {
            board.board[file][rank].piece.image = temp;
        }
        
        //

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
