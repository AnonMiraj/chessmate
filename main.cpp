#include <iostream>
#include <vector>
#include <map>

#include "raylib.h"

#include "square.h"
#include "board.h"

using namespace std;

int main() {
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    const int squareWidth = screenWidth/8;

    InitWindow(screenWidth, screenHeight, "Chessmate");

    Board board;
    int s = 0;

    SetTargetFPS(60); 
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Square* square = board.getCurrentSquare(GetMouseX(), GetMouseY());

        if (square->hasP) {
            SetMouseCursor(4);
        } else {
            SetMouseCursor(0);
        }

        if (IsMouseButtonPressed(1)) { // right click
            int tmpSqr = board.tmpSqr;
            int tmpNum = board.tmpNum;

            board[tmpSqr][tmpNum].assign(board.tmp, board.tmpPieceType);
            board.tmpPieceType = 0;
            //tmp = empty;
            s=0;
        }

        if (IsMouseButtonPressed(0)) {
            if (!s) {
                board.tmpPieceType = square->pieceType;
                board.tmp = square->image;
                board.assignable = square->hasP;
                square->removeTexture();
                board.tmpSqr = square->file;
                board.tmpNum = square->rank;
                board.tmpX = square->rec.x;
                board.tmpY = square->rec.y;
                s=1;
            } else {
                if (board.assignable) {
                    int tmpSqr = tmpSqr;
                    int tmpNum = tmpNum;

                    square->assign(board.tmp, board.tmpPieceType);
                    board[tmpSqr][tmpNum].removeTexture();
                    board.tmp = board.empty;
                }
                s=0;
            }
        }

        if (IsMouseButtonReleased(0)) {
            if (board.assignable && square->pieceType != board.tmpPieceType) {
                square->assign(board.tmp, board.tmpPieceType);
                //board[tmpSqr][tmpNum].removeTexture();
            } else {
                int tmpSqr = board.tmpSqr;
                int tmpNum = board.tmpNum;

                board[tmpSqr][tmpNum].assign(board.tmp, board.tmpPieceType);
            }
            board.tmp = board.empty;
            s=0;
        }

        if (IsMouseButtonReleased(1)) {
            // TODO: The right click release now is kinda ugly, this needs to be implemented.
        }

        for(char ch = 'a'; ch <= 'h'; ch++) {
            for(int i = 1; i <= 8; i++) {
                Square sq = board[ch][i];
                DrawRectangleRec(sq.rec, sq.color);
                DrawTexture(sq.image, sq.rec.x, sq.rec.y, WHITE);
            }
        }

        DrawTexture(board.tmp, GetMouseX()-50, GetMouseY()-50, WHITE);

        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
