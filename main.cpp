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

    Piece temp_piece;
    Texture2D temp;
    Texture2D empty;

    while (!WindowShouldClose()) {
        BeginDrawing();

        int x = GetMousePosition().x;
        int y = GetMousePosition().y;

        for(int idx = 1; idx <= 8; idx++) {
            for(char ch = 'a'; ch <= 'h'; ch++) {
                Square square = board.board[ch][idx];
                int posX = square.x;
                int posY = square.y;

                if (x >= posX && x <= (posX+125) && y >= posY && y <= (posY+125)) {
                    file = square.file;
                    rank = square.rank;
                }

                DrawRectangle(posX, posY, squareWidth, squareWidth, square.color);
                DrawTexture(square.piece.image, square.x, square.y, WHITE);
            }
        }

        if (IsMouseButtonPressed(0)) {
            if (board.board[file][rank].piece.piece_color == board.turn) {
                temp = board.board[file][rank].piece.image;
                temp_piece = board.board[file][rank].piece;
                board.board[file][rank].piece.image = empty;
                board.assign_ok = 1;
            } else {
                board.assign_ok = 0;
            }
        }

        if (IsMouseButtonDown(0)) {
            DrawTexture(temp, x-60, y-60, WHITE);
        }

        if (IsMouseButtonReleased(0) && board.assign_ok) {
            board.board[file][rank].piece = temp_piece;
            temp = empty;
            board.turn = board.turn == P_WHITE ? P_BLACK : P_WHITE;
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
